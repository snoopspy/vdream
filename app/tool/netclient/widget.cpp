#include "widget.h"
#include "ui_widget.h"
#include <VDebugNew>

// ----------------------------------------------------------------------------
// ClientThread
// ----------------------------------------------------------------------------
ClientThread::ClientThread(void* owner, VNetClient* netClient) : VThread(owner)
{
  this->widget    = (Widget*)owner;
  this->netClient = netClient;
}

ClientThread::~ClientThread()
{
  close();
}

void ClientThread::fireEvent(QEvent* event)
{
  QApplication::postEvent(widget, event);
}

void ClientThread::run()
{
  LOG_ASSERT(netClient != NULL);
  fireEvent(new StateEvent(VState::Opening));

  bool res = netClient->open();
  if (!res)
  {
    fireEvent(new MsgEvent(netClient->error.msg, QThread::currentThreadId()));
    fireEvent(new CloseEvent);
    return;
  }

  if (dynamic_cast<VUdpClient*>(netClient) == NULL)
  {
    fireEvent(new MsgEvent("******** connected ********\r\n", QThread::currentThreadId()));
  }
  fireEvent(new StateEvent(VState::Opened));

  while (true)
  {
    QByteArray ba;

    int readLen = netClient->read(ba);
    if (readLen == VError::FAIL) break;

    if (widget->ui->chkShowHexa->checkState() == Qt::Checked)
      ba = ba.toHex();
    QString msg = ba;
    fireEvent(new MsgEvent(msg, QThread::currentThreadId()));
  }

  if (dynamic_cast<VUdpClient*>(netClient) == NULL)
  {
    fireEvent(new MsgEvent("******** disconnected ********\r\n", QThread::currentThreadId()));
  }
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
  netClient    = NULL;
  clientThread = NULL;

  move(0, 0); resize(640, 480);

  setLayout(ui->mainLayout);
  ui->mainLayout->setSpacing(0);
  ui->pteRecv->setWordWrapMode(QTextOption::NoWrap);
  ui->pteSend->setWordWrapMode(QTextOption::NoWrap);
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
      case 0: netClient = &tcpClient; break;
      case 1: netClient = &udpClient; break;
      case 2: netClient = &sslClient; break;
    }
    state = netClient->state();
  }

  ui->pbOpen->setEnabled(state == VState::Closed);
  ui->pbClose->setEnabled(state != VState::Closed);
  ui->tabOption->setEnabled(state == VState::Closed);
  ui->pbSend->setEnabled(state == VState::Opened);
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
  ui->tabOption->setCurrentIndex(rep.getInt("currentIndex", 0));
  ui->leTcpHost->setText(rep.getStr("tcpHost", ui->leTcpHost->text()));
  ui->leTcpPort->setText(rep.getStr("tcpPort", ui->leTcpPort->text()));
  ui->leUdpHost->setText(rep.getStr("udpHost", ui->leUdpHost->text()));
  ui->leUdpPort->setText(rep.getStr("udpPort", ui->leUdpPort->text()));
  ui->leSslHost->setText(rep.getStr("sslHost", ui->leSslHost->text()));
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

  tcpClient.load(rep.gotoChilds("netClient/tcpClient"));
  udpClient.load(rep.gotoChilds("netClient/udpClient"));
  sslClient.load(rep.gotoChilds("netClient/sslClient"));
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
  rep.setInt("currentIndex", ui->tabOption->currentIndex());
  rep.setStr("tcpHost", ui->leTcpHost->text());
  rep.setStr("tcpPort", ui->leTcpPort->text());
  rep.setStr("udpHost", ui->leUdpHost->text());
  rep.setStr("udpPort", ui->leUdpPort->text());
  rep.setStr("sslHost", ui->leSslHost->text());
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

  tcpClient.save(rep.gotoChilds("netClient/tcpClient"));
  udpClient.save(rep.gotoChilds("netClient/udpClient"));
  sslClient.save(rep.gotoChilds("netClient/sslClient"));
}

void Widget::on_pbOpen_clicked()
{
  int currentIndex = ui->tabOption->currentIndex();
  switch (currentIndex)
  {
    case 0:
      tcpClient.host = ui->leTcpHost->text();
      tcpClient.port = ui->leTcpPort->text().toInt();
      netClient = &tcpClient;
      break;
    case 1:
      udpClient.host = ui->leUdpHost->text();
      udpClient.port = ui->leUdpPort->text().toInt();
      netClient = &udpClient;
      break;
    case 2:
      sslClient.host = ui->leSslHost->text();
      sslClient.port = ui->leSslPort->text().toInt();
      netClient = &sslClient;
      break;
  }

  SAFE_DELETE(clientThread);
  clientThread = new ClientThread(this, netClient);
  clientThread->open();

  setControl();
}

void Widget::on_pbClose_clicked()
{
  LOG_ASSERT(netClient != NULL);
  netClient->close();
  SAFE_DELETE(clientThread);
  setControl();
}

void Widget::on_pbClear_clicked()
{
  ui->pteRecv->clear();
}

void Widget::on_tbTcpAdvance_clicked()
{
  if (tcpClient.optionDoAll(this))
  {
    ui->leTcpHost->setText(tcpClient.host);
    ui->leTcpPort->setText(QString::number(tcpClient.port));
  }
}

void Widget::on_tbUdpAdvence_clicked()
{
  if (udpClient.optionDoAll(this))
  {
    ui->leUdpHost->setText(udpClient.host);
    ui->leUdpPort->setText(QString::number(udpClient.port));
  }
}

void Widget::on_tbSslAdvanced_clicked()
{
  if (sslClient.optionDoAll(this))
  {
    ui->leSslHost->setText(sslClient.host);
    ui->leSslPort->setText(QString::number(sslClient.port));
  }
}

void Widget::on_pbSend_clicked()
{
  if (netClient == NULL) return;
  QByteArray ba = qPrintable(ui->pteSend->toPlainText());
  ba = ba.replace("\n", "\r\n");
  if (ui->chkSendHexa->checkState() == Qt::Checked) ba = ba.fromHex(ba);
  netClient->write(ba);
}
