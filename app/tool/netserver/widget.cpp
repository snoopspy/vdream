#include "widget.h"
#include "ui_widget.h"

// ----------------------------------------------------------------------------
// UdpServerThread
// ----------------------------------------------------------------------------
UdpServerThread::UdpServerThread(void* owner, VUdpServer* udpServer)
{
  this->widget    = (Widget*)owner;
  this->udpServer = udpServer;
}

UdpServerThread::~UdpServerThread()
{
  close();
}

void UdpServerThread::fireEvent(QEvent* event)
{
  QApplication::postEvent(widget, event);
}

void UdpServerThread::run()
{
  LOG_ASSERT(udpServer != NULL);
  VSockAddrList& sockAddrList = udpServer->sockAddrList; // for abbreviate
  VUdpSession* udpSession = udpServer->udpSession; // for abbreviate

  // fireEvent(new MsgEvent("******** connected ********")); // gilgil temp 2014.03.01
  fireEvent(new StateEvent(VState::Opened));
  while (active())
  {
    QByteArray ba;
    int readLen = udpServer->read(ba);

    //
    // Delete session
    //
    if (readLen == VError::FAIL)
    {
      QString msg = udpSession->error.msg;
      fireEvent(new MsgEvent(msg, QThread::currentThreadId()));

      if (udpSession->error.code == 10054/*WSAECONNRESET*/) // ICMP Destination Unreachable // gilgil temp 2014.04.18
      {
        while (true)
        {
          VSockAddrList::iterator it = sockAddrList.findByInAddr(udpSession->addr.sin_addr);
          if (it == sockAddrList.end()) break;
          sockAddrList.erase(it);
        }
        LOG_DEBUG("count=%zu", sockAddrList.size()); // gilgi temp 2009.08.16
      } else // other error
      {
        VSockAddrList::iterator it = sockAddrList.findBySockAddr(udpSession->addr);
        if (it != sockAddrList.end())
          sockAddrList.erase(it);
        LOG_DEBUG("count=%zu", sockAddrList.size()); // gilgi temp 2009.08.16
      }
      udpSession->error.clear();
      continue;
    }

    //
    // Add session
    //
    if (sockAddrList.findBySockAddr(udpSession->addr) == sockAddrList.end())
    {
      struct sockaddr_in* newSockAddr = new struct sockaddr_in;
      *newSockAddr = udpSession->addr;
      sockAddrList.insert(*newSockAddr);
      LOG_DEBUG("count=%zu", sockAddrList.size()); // gilgi temp 2009.08.16
    }

    if (widget->ui->chkShowHexa->checkState() == Qt::Checked)
      ba = ba.toHex();
    QString msg = ba;
    fireEvent(new MsgEvent(msg, QThread::currentThreadId()));

    if (widget->ui->chkEcho->checkState() == Qt::Checked)
    {
      if (widget->ui->chkEchoBroadcast->checkState() == Qt::Checked)
      {
        udpServer->write(ba); // do not check result
      } else
      {
        int writeLen = udpSession->write(ba);
        if (writeLen == VError::FAIL) break;
      }
    }
  }
  // fireEvent(new MsgEvent("******** disconnected ********")); // gilgil temp 2014.03.01
  fireEvent(new CloseEvent);
}

// ----------------------------------------------------------------------------
// Widget
// ----------------------------------------------------------------------------
Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  initializeControl();
}

Widget::~Widget()
{
  saveControl();
  finalizeControl();
  delete ui;
}

void Widget::initializeControl()
{
  netServer       = NULL;
  udpServerThread = NULL;

  move(0, 0); resize(640, 480);

  setLayout(ui->mainLayout);
  ui->mainLayout->setSpacing(0);
  ui->pteRecv->setWordWrapMode(QTextOption::NoWrap);
  ui->pteSend->setWordWrapMode(QTextOption::NoWrap);

  VObject::connect(&tcpServer, SIGNAL(runned(VTcpSession*)), this, SLOT(tcpRun(VTcpSession*)), Qt::DirectConnection);
  VObject::connect(&sslServer, SIGNAL(runned(VSslSession*)), this, SLOT(sslRun(VSslSession*)), Qt::DirectConnection);
}

void Widget::finalizeControl()
{
  on_pbClose_clicked();
}

void Widget::loadControl()
{
  this->loadFromDefaultDoc("MainWindow");
}

void Widget::saveControl()
{
  this->saveToDefaultDoc("MainWindow");
}

void Widget::setControl(VState state)
{
  LOG_DEBUG(""); // gilgil temp 2014.02.28
  if (state == VState::None)
  {
    int currentIndex = ui->tabOption->currentIndex();
    switch (currentIndex)
    {
      case 0: netServer = &tcpServer; break;
      case 1: netServer = &udpServer; break;
      case 2: netServer = &sslServer; break;
    }
    state = netServer->state();
  }

  ui->pbOpen->setEnabled(state == VState::Closed);
  ui->pbClose->setEnabled(state != VState::Closed);
  ui->tabOption->setEnabled(state == VState::Closed);
  ui->pbSend->setEnabled(state == VState::Opened);
}

void Widget::tcpRun(VTcpSession* tcpSession)
{
  myRun(tcpSession);
}

void Widget::sslRun(VSslSession* sslSession)
{
  myRun(sslSession);
}

void Widget::fireEvent(QEvent* event)
{
  QApplication::postEvent(this, event);
}

void Widget::myRun(VNetSession* netSession)
{
  LOG_ASSERT(netSession != NULL);

  fireEvent(new MsgEvent("******** connected ********", QThread::currentThreadId()));

  while (true)
  {
    QByteArray ba;

    int readLen = netSession->read(ba);
    if (readLen == VError::FAIL) break;

    if (ui->chkShowHexa->checkState() == Qt::Checked)
      ba = ba.toHex();
    QString msg = ba;
    fireEvent(new MsgEvent(msg, QThread::currentThreadId()));

    if (ui->chkEcho->checkState() == Qt::Checked)
    {
      if (ui->chkEchoBroadcast->checkState() == Qt::Checked)
      {
        netServer->write(ba); // do not check result
      } else
      {
        int writeLen = netSession->write(ba);
        if (writeLen == VError::FAIL) break;
      }
    }
  }

  fireEvent(new MsgEvent("******** disconnected ********", QThread::currentThreadId())); // gilgil temp 2014.03.01
  // fireEvent(new CloseEvent); // gilgil temp 2014.03.01
}

bool Widget::event(QEvent* event)
{
  StateEvent* stateEvent = dynamic_cast<StateEvent*>(event);
  if (stateEvent != NULL)
  {
    setControl();
    return true;
  }

  MsgEvent* msgEvent = dynamic_cast<MsgEvent*>(event);
  if (msgEvent != NULL)
  {
    showMessage(msgEvent);
    return true;
  }

  CloseEvent* closeEvent = dynamic_cast<CloseEvent*>(event);
  if (closeEvent != NULL)
  {
    ui->pbClose->click();
    return true;
  }

  return QWidget::event(event);
}

void Widget::showEvent(QShowEvent* showEvent)
{
  loadControl();
  setControl();
  QWidget::showEvent(showEvent);
}

void Widget::showMessage(MsgEvent* event)
{
  static Qt::HANDLE lastThreadId = 0;
  if (lastThreadId != 0 && lastThreadId != event->threadId) event->msg = QString("\r\n") + event->msg;
  lastThreadId = event->threadId;
  ui->pteRecv->insertPlainText(event->msg);
  ui->pteRecv->ensureCursorVisible();
}

void Widget::load(VRep& rep)
{
  {
    VXml coordXml = rep.findChild("coord");
    if (!coordXml.isNull())
    {
      QRect rect = geometry();
      rect.setLeft  ((coordXml.getInt("left",   0)));
      rect.setTop   ((coordXml.getInt("top",    0)));
      rect.setWidth ((coordXml.getInt("width",  640)));
      rect.setHeight((coordXml.getInt("height", 480)));
      setGeometry(rect);
    }
  }

  ui->chkShowHexa->setCheckState((Qt::CheckState)rep.getInt("showHexa", (int)ui->chkShowHexa->checkState()));
  ui->chkSendHexa->setCheckState((Qt::CheckState)rep.getInt("sendHexa", (int)ui->chkSendHexa->checkState()));
  ui->chkEcho->setCheckState((Qt::CheckState)rep.getInt("echo", (int)ui->chkEcho->checkState()));
  ui->chkEchoBroadcast->setCheckState((Qt::CheckState)rep.getInt("echoBroadcast", (int)ui->chkEchoBroadcast->checkState()));
  ui->tabOption->setCurrentIndex(rep.getInt("currentIndex", 0));
  ui->leTcpPort->setText(rep.getStr("tcpPort", ui->leTcpPort->text()));
  ui->leUdpPort->setText(rep.getStr("udpPort", ui->leUdpPort->text()));
  ui->leSslPort->setText(rep.getStr("sslPort", ui->leSslPort->text()));
  ui->pteSend->insertPlainText(rep.getStr("sendText", ui->pteSend->toPlainText()));

  {
    VXml sizesXml = rep.findChild("sizes");
    QList<int> sizes;
    if (!sizesXml.isNull())
    {
      QStringList strList = sizesXml.getStr("splitter").split(",");
      foreach (QString s, strList) sizes << s.toInt();
      ui->splitter->setSizes(sizes);
    }
  }

  tcpServer.load(rep.gotoChilds("netClient/tcpServer"));
  udpServer.load(rep.gotoChilds("netClient/udpServer"));
  sslServer.load(rep.gotoChilds("netClient/sslServer"));
}

void Widget::save(VRep& rep)
{
  {
    VXml coordXml = rep.gotoChild("coord");
    QRect rect = geometry();
    coordXml.setInt("left",   rect.left());
    coordXml.setInt("top",    rect.top());
    coordXml.setInt("width",  rect.width());
    coordXml.setInt("height", rect.height());
  }

  rep.setInt("showHexa", (int)ui->chkShowHexa->checkState());
  rep.setInt("sendHexa", (int)ui->chkSendHexa->checkState());
  rep.setInt("echo", (int)ui->chkEcho->checkState());
  rep.setInt("echoBroadcast", (int)ui->chkEchoBroadcast->checkState());
  rep.setInt("currentIndex", ui->tabOption->currentIndex());
  rep.setStr("tcpPort", ui->leTcpPort->text());
  rep.setStr("udpPort", ui->leUdpPort->text());
  rep.setStr("sslPort", ui->leSslPort->text());
  rep.setStr("sendText", ui->pteSend->toPlainText());

  {
    VXml sizesXml = rep.gotoChild("sizes");
    QList<int> sizes = ui->splitter->sizes();
    QString strList;
    strList.clear(); foreach (int size, sizes) strList += QString::number(size) + ",";
    strList = strList.left(strList.count() - 1);
    sizesXml.setStr("splitter", strList);
  }

  tcpServer.save(rep.gotoChilds("netClient/tcpServer"));
  udpServer.save(rep.gotoChilds("netClient/udpServer"));
  sslServer.save(rep.gotoChilds("netClient/sslServer"));
}

void Widget::on_pbOpen_clicked()
{
  int currentIndex = ui->tabOption->currentIndex();
  switch (currentIndex)
  {
    case 0:
      tcpServer.port = ui->leTcpPort->text().toInt();
      netServer = &tcpServer;
      break;
    case 1:
      udpServer.port = ui->leUdpPort->text().toInt();
      netServer = &udpServer;
      break;
    case 2:
      sslServer.port = ui->leSslPort->text().toInt();
      netServer = &sslServer;
      break;
  }

  bool res = netServer->open();
  if (!res)
  {
    QString msg = netServer->error.msg;
    MsgEvent msgEvent(msg + "\r\n", QThread::currentThreadId());
    showMessage(&msgEvent);
    return;
  }
  if (netServer == &udpServer)
  {
    SAFE_DELETE(udpServerThread);
    udpServerThread = new UdpServerThread(this, &udpServer);
    udpServerThread->open();
  }

  setControl();
}

void Widget::on_pbClose_clicked()
{
  LOG_ASSERT(netServer != NULL);
  netServer->close();
  SAFE_DELETE(udpServerThread);
  setControl();
}

void Widget::on_pbClear_clicked()
{
  ui->pteRecv->clear();
}

void Widget::on_tbTcpAdvance_clicked()
{
  if (tcpServer.optionDoAll(this))
  {
    ui->leTcpPort->setText(QString::number(tcpServer.port));
  }
}

void Widget::on_tbUdpAdvence_clicked()
{
  if (udpServer.optionDoAll(this))
  {
    ui->leTcpPort->setText(QString::number(udpServer.port));
  }
}

void Widget::on_tbSslAdvanced_clicked()
{
  if (sslServer.optionDoAll(this))
  {
    ui->leTcpPort->setText(QString::number(sslServer.port));
  }
}

void Widget::on_pbSend_clicked()
{
  if (netServer == NULL) return;
  QByteArray ba = qPrintable(ui->pteSend->toPlainText());
  ba = ba.replace("\n", "\r\n");
  if (ui->chkSendHexa->checkState() == Qt::Checked) ba = ba.fromHex(ba);
  netServer->write(ba);
}
