#include <VThread>
#include <VDebugNew>

// ----- gilgil temp 2014.12.25 -----
__thread int threadTag = 0;
// ----------------------------------

// ----- gilgil temp 2014.12.09 -----
/*
#ifdef _MSC_VER
#pragma pack(push, 1)
typedef struct
{
  DWORD recType;
  char* name;
  DWORD threadID;
  DWORD flags;
} ThreadNameInfo;
#pragma pack (pop)
#endif // _MSC_VER

static void _setCurrentThreadName(const char* name) // for debugging
{
#if _MSC_VER
  ThreadNameInfo info;
  info.recType  = 0x1000;
  info.name     = (char*)name;
  info.threadID = 0xFFFFFFFF;
  info.flags    = 0;
  __try
  {
    RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR*)(&info));
  }
  __except(1)
  {
  }
#else
  Q_UNUSED(name)
#endif // _MSC_VER
}
*/
// ----------------------------------

// ----------------------------------------------------------------------------
// VQThread
// ----------------------------------------------------------------------------
VQThread::VQThread(void* owner) : QThread(NULL)
//VQThread::VQThread(void* owner) : QThread((QObject*)owner) // gilgil temp 2012.11.27
{
  this->owner = owner;
  // ----- gilgil temp 2012.08.16 -----
  /*
  {
    QThread* qthread = dynamic_cast<QThread*>(this);
    LOG_DEBUG("qthread=%p", qthread);
  }
  */
  // ----------------------------------
}

VQThread::~VQThread()
{
  // ----- gilgil temp 2012.08.16 -----
  /*
  {
    QThread* qthread = dynamic_cast<QThread*>(this);
    LOG_DEBUG(" qthread=%p", qthread);
  }
  */
  // ----------------------------------
}

void VQThread::_run()
{
  VThread* thread = (VThread*)owner;
  try
  {
    // msleep(1000); // to occur virtual function call error // gilgil temp 2011.10.09
    thread->run();
  } catch (...)
  {
    throw std::exception();
  }
}

void VQThread::run()
{
  VThread* thread = (VThread*)owner;

  char threadName[VBase::BUF_SIZE];
  char className [VBase::BUF_SIZE];

  try
  {
    if (thread->name == "") thread->name = thread->className();
	strncpy(threadName, qPrintable(thread->name), VBase::BUF_SIZE);
	strncpy(className, qPrintable(thread->className()), VBase::BUF_SIZE);
    // _setCurrentThreadName((char*)threadName); // gilgil temp 2014.12.09

    thread->m_id = VThread::currentId();

    try
    {
      _run();
    }
    catch (...)
    {
      LOG_FATAL("%p oops1 exception threadName=%s className=%s tag=%d threadTag=%d", thread, threadName, className, thread->tag, threadTag);
    }

    bool freeThread = thread->freeOnTerminate;
    if (freeThread)
    {
      // ----- gilgil temp 2015.01.22 -----
      /*
      VDeleteObjectEvent* event = new VDeleteObjectEvent(thread);
      VEventHandler::instance().postEvent(event);
      // msleep(1000); // gilgil temp 2012.12.10
      */
      thread->deleteLater();
      // ----------------------------------
    }
  }
  catch(...)
  {
    LOG_FATAL("%p oops2 exception threadName=%s className=%s tag=%d threadTag=%d", thread, threadName, className, thread->tag, threadTag);
  }
}

// ----------------------------------------------------------------------------
// VThread
// ----------------------------------------------------------------------------
// VThread::VThread(void* owner) : VObject(owner) // gilgil temp 2012.09.18
VThread::VThread(void* owner) : VObject(NULL)
{
  this->owner = owner;
  // ----- gilgil temp 2012.08.16 -----
  /*
  {
    VThread* thread = dynamic_cast<VThread*>(this);
    LOG_DEBUG("thread=%p", thread);
  }
  */
  // ----------------------------------
  m_id            = 0; // m_id is determined in VQThread::run()
  m_qthread       = NULL;
  freeOnTerminate = false;
  threadPriority  = QThread::NormalPriority;
  VThreadMgr& mgr = VThreadMgr::instance();
  mgr.lock();
  mgr.add(this);
  mgr.unlock();
}

VThread::~VThread()
{
  // ----- gilgil temp 2012.08.16 -----
  /*
  {
    VThread* thread = dynamic_cast<VThread*>(this);
    LOG_DEBUG("thread=%p", thread);
  }
  */
  // ----------------------------------
  close(true);
  SAFE_DELETE(m_qthread);
  VThreadMgr& mgr = VThreadMgr::instance();
  mgr.lock();
  mgr.del(this);
  mgr.unlock();
}

bool VThread::open()
{
  VLock lock(m_cs);
  return VObject::open();
}

bool VThread::close()
{
  return close(true);
}

bool VThread::close(bool wait, VTimeout timeout)
{
  VLock lock(m_cs);

  // LOG_DEBUG("tag=%d state=%d", tag, (int)m_state); // gilgil temp 2011.10.10
  if (m_state == VState::Closed) // if already closed
  {
    return true;
  }

  // Even though m_state is already changed into Closing by other caller,
  // if wait is true, waitFor must be called.
  // So close method include 2 state conditions(Opened, Closing).
  if (m_state != VState::Opened && m_state != VState::Closing)
  {
    return false;
  }

  m_state = VState::Closing;
  if (wait)
  {
    bool res = this->wait(timeout);
    // set m_state info Closed even if waitfor return false so as to not call waitFor any more.
    m_state = VState::Closed;
    return res;
  }
  return true;
}

bool VThread::wait(VTimeout timeout)
{
  VLock lock(m_cs);

  {
    Qt::HANDLE calling_id = currentId();
    Qt::HANDLE closing_id = this->id();
    if (calling_id == closing_id)
    {
      LOG_WARN("*******************************************************************");
      LOG_WARN("self wait? id=0x%p tag=%d state=%d threadTag=%d", calling_id, tag, (int)m_state, threadTag);
      LOG_WARN("*******************************************************************");
    }
  }

  bool res = true;
  // LOG_DEBUG("%s m_qthread=%p", qPrintable(name), m_qthread); // gilgil temp 2012.05.29
  if (m_qthread)
  {
    res = m_qthread->wait(timeout);
    if (!res)
    {
      LOG_ERROR("**********************************************************************");
      SET_ERROR(VThreadError, QString("thread(%1) timeout id=0x%2 tag=%3 threadTag=%4").arg(name).arg((quintptr)id(), 0, 16).arg(tag).arg(threadTag), VError::TIMEOUT);
      LOG_ERROR("**********************************************************************");
      return false;
    }
    SAFE_DELETE(m_qthread);
  }
  // LOG_DEBUG("%s res=%d",  qPrintable(name), res); // gilgil temp 2012.05.29
  return res;
}

bool VThread::doOpen()
{
  if (m_qthread) delete m_qthread;
  m_qthread = new VQThread(this);

  VThreadMgr& mgr = VThreadMgr::instance();
  mgr.lock();
  if (!mgr.suspending())
    m_qthread->start(threadPriority);
  mgr.unlock();
  return true;
}

bool VThread::doClose()
{
  return wait();
}

void VThread::run()
{
  LOG_ERROR("****************************************************");
  LOG_ERROR("%s : virtual function call error.", qPrintable(name));
  LOG_ERROR("'virtual void run()' must be implemented in descendant class of VThread.");
  LOG_ERROR("if descendant class has destructor, close() must be called explicitly in its destructor");
  LOG_ERROR("****************************************************");
}

void VThread::load(VRep& rep)
{
  VObject::load(xml);

  freeOnTerminate = rep.getBool("freeOnTerminate", freeOnTerminate);
  threadPriority  = (QThread::Priority) rep.getInt("threadPriority", (int)threadPriority);
}

void VThread::save(VRep& rep)
{
  VObject::save(xml);

  rep.setBool("freeOnTerminate", freeOnTerminate);
  rep.setInt("threadPriority", (int)threadPriority);
}

// ----------------------------------------------------------------------------
// VThreadMgr
// ----------------------------------------------------------------------------
VThreadMgr::VThreadMgr()
{
  VLock _lock(*this);
  m_suspending = false;
  clear(false);
}

VThreadMgr::~VThreadMgr()
{
  VLock _lock(*this);

  int _count = threadList.count();
  if (_count != 0)
  {
    LOG_FATAL("thread list count is not zero(%d)", _count);
  }
  clear(true);
}

void VThreadMgr::clear(bool checkLeak)
{
  VLock _lock(*this);

  if (checkLeak)
  {
    int _count = threadList.count();
    if (_count != 0)
    {
      LOG_FATAL("thread list count is not zero(%d). Call threadList.clear() before call clear", _count);
    }
  }
  threadList.clear();
}

void VThreadMgr::add(VThread* thread)
{
  VLock _lock(*this);

  threadList.push_back(thread);
}

void VThreadMgr::del(VThread* thread)
{
  VLock _lock(*this);

  int i = threadList.indexOf(thread);
  if (i == -1)
  {
    LOG_ERROR("can not find thread(%p)", thread);
    return;
  }
  threadList.removeAt(i);
}

void VThreadMgr::suspend()
{
  VLock _lock(*this);

  m_suspending = true;
}

void VThreadMgr::resume()
{
  VLock _lock(*this);

  int _count = threadList.count();
  for (int i = 0; i < _count; i++)
  {
    VThread* thread = threadList.at(i);

    if (thread == NULL) continue;
    // if (thread->active()) continue; // gilgil temp 2012.08.25

    VQThread* qthread = thread->m_qthread;
    if (qthread == NULL) continue;
    if (qthread->isRunning()) continue;
    if (qthread->isFinished()) continue;

    thread->m_qthread->start(thread->threadPriority);
  }
  m_suspending = false;
}

// ----------------------------------------------------------------------------
// VSimpleThread
// ----------------------------------------------------------------------------
VSimpleThread::VSimpleThread(VThreadFunc threadFunc, void* p, VRunnable* runnable)
{
  m_threadFunc = threadFunc;
  m_p          = p;
  m_runnable   = runnable;
}

VSimpleThread::~VSimpleThread()
{
  close();
}

bool VSimpleThread::open()
{
  if (name == "")
  {
    if (m_runnable != NULL)
    {
      try
      {
		name = QString(VBase::getClassName(typeid(*m_runnable).name()))+ "::run";
      }
      catch(...)
      {
        name = "SimpleThread";
      }
    }
    else
    {
	  name = VBase::getClassName(typeid(*this).name());
    }
  }
  return VThread::open();
}

void VSimpleThread::run()
{
  m_threadFunc(m_p);
}

#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>
#include <VMemoryLeak>

// ----------------------------------------------------------------------------
// basicThread
// ----------------------------------------------------------------------------
class MyThread : public VThread
{
protected:
  int m_n;
public:
  MyThread(int n) : m_n(n) {};
  virtual ~MyThread() { close(); }
protected:
  virtual void run()
  {
    for (int i = 0; i < 3; i ++)
    {
      msleep(100);
      printf("%p thread %d\n", VThread::currentId(), m_n);
    }
  }
};

TEST( Thread, basicThreadTest )
{
  static const int THREAD_CNT = 5;
  MyThread* myThread[THREAD_CNT];

  for (int i = 0; i < THREAD_CNT; i++)
  {
    myThread[i] = new MyThread(i);
    myThread[i]->open();
  }
  printf("%p closing all threads...\n", VThread::currentId());
  for (int i = 0; i < THREAD_CNT; i++)
  {
    myThread[i]->close();
    delete myThread[i];
  }
  printf("%p all threads closed\n", VThread::currentId());
}

// ----------------------------------------------------------------------------
// simpleThread
// ----------------------------------------------------------------------------
void threadFunc(void* p)
{
  LOG_DEBUG("threadFunc %p", p);
};

TEST( Thread, simpleThreadTest )
{
  LOG_DEBUG("simpleThread");
  VSimpleThread st(threadFunc, (void*)0x12345678);
  EXPECT_TRUE( st.open() );
  EXPECT_TRUE( st.close() );
}

// ----------------------------------------------------------------------------
// runnable
// ----------------------------------------------------------------------------
class MyRunnableObject : public VRunnable
{
protected:
  virtual void run()
  {
    LOG_DEBUG("running...");
  }
};

TEST( Thread, runnableTest )
{
  LOG_DEBUG("runnable");
  MyRunnableObject obj;
  EXPECT_TRUE( obj.runThread().open() );
  EXPECT_TRUE( obj.runThread().wait() );
  EXPECT_TRUE( obj.runThread().close() );
}

// ----------------------------------------------------------------------------
// openClose
// ----------------------------------------------------------------------------
volatile static int debugCnt = 0;
static VCS openCloseCS;
class OpenCloseThread : public VThread
{
protected:
  virtual void run() {
    openCloseCS.lock();
    debugCnt++;
    openCloseCS.unlock();
  }
};

TEST( Thread, openCloseTest )
{
  static const int OPEN_CLOSE_CNT = 1000; // gilgil temp 2012.05.29

  OpenCloseThread* thread[OPEN_CLOSE_CNT];
  for (int i= 0 ; i < OPEN_CLOSE_CNT; i++)
  {
    thread[i] = new OpenCloseThread;
  }
  for (int i = 0; i < OPEN_CLOSE_CNT; i++)
  {
    bool res = thread[i]->open();
    if (!res)
    {
      printf("thread.open() return false i=%d\n", i);
      msleep(1000);
    }
    EXPECT_TRUE( res );
  }
  for (int i = 0; i < OPEN_CLOSE_CNT; i++)
  {
    EXPECT_TRUE ( thread[i]->close() );
  }
  for (int i = 0; i < OPEN_CLOSE_CNT; i++)
  {
    delete thread[i];
  }

  LOG_DEBUG("debugCnt=%d",debugCnt);
  EXPECT_EQ( debugCnt, OPEN_CLOSE_CNT );
}

// --------------------------------------------------------------------------
// timeout
// --------------------------------------------------------------------------
class TimeoutThread : public VThread
{
protected:
  virtual void run()
  {
    msleep(1000);
  }
};

TEST( Thread, timeoutTest )
{
  {
    TimeoutThread thread;
    thread.open();

    LOG_INFO("Thread timeout will occur. Don't worry. :)");
    int oldLevel = getLog()->level;
    getLog()->level = VLog::LEVEL_NONE;

    bool res = thread.wait(500);
    EXPECT_TRUE( res == false );

    getLog()->level = oldLevel;
  }

  {
    TimeoutThread thread;
    thread.open();
    bool res = thread.wait(1500);
    EXPECT_TRUE( res == true );
  }
}

// ----- gilgil temp 2014.12.25 -----
/*
// --------------------------------------------------------------------------
// exception
// --------------------------------------------------------------------------
class ExceptionThread : public VThread
{
protected:
  virtual void run()
  {
    tag   = 100;
    int i = 5;
    tag   = 200;
    int j = 0;
    tag   = 300;
    int k = i / j; // occur exception
    tag   = 400;
    printf("i=%d j=%d k=%d\n", i, j, k);
    tag   = 500;
  }
};

TEST( Thread, exceptionTest )
{
  ExceptionThread thread;
  thread.open();
  LOG_INFO("Exception will occur. Don't worry. :)");
  bool res = thread.wait();
  EXPECT_TRUE( res == true );
  EXPECT_EQ( thread.tag , 300 );
}
*/
// ----------------------------------

// --------------------------------------------------------------------------
// multiWait
// --------------------------------------------------------------------------
class RunThread : public VThread
{
protected:
  virtual void run()
  {
    msleep(5000);
  }
};

class WaitThread : public VThread
{
public:
  RunThread* runThread;
public:
  WaitThread(RunThread* runThread) { this->runThread = runThread; }
protected:
  virtual void run()
  {
    msleep(1000);
    runThread->close();
  }
};

TEST( Thread, multiWaitTest )
{
  static const int WAIT_THREAD_CNT = 1;

  VMemoryLeak::start(false);
  {
    RunThread runThread;
    EXPECT_TRUE( runThread.open() );

    WaitThread* waitThread[WAIT_THREAD_CNT];
    for (int i = 0; i < WAIT_THREAD_CNT; i++)
    {
      waitThread[i] = new WaitThread(&runThread);
      EXPECT_TRUE( waitThread[i]->open() );
    }

    for (int i = 0; i < WAIT_THREAD_CNT; i++)
    {
      EXPECT_TRUE( waitThread[i]->close() );
    }

    for (int i = 0; i < WAIT_THREAD_CNT; i++)
    {
      waitThread[i]->close();
      delete waitThread[i];
    }

    runThread.close();
  }
  VMemoryLeak::stop(false);
}

// --------------------------------------------------------------------------
// virtualFunctionCallError
// --------------------------------------------------------------------------
static int succeedCnt = 0;
static VCS virtualFunctionCallErrorCS;
class NoDestructorThread : public VThread
{
public:
  // virtual ~NoDestructorThread() { close(); }
protected:
  virtual void run()
  {
    virtualFunctionCallErrorCS.lock();
    succeedCnt++;
    virtualFunctionCallErrorCS.unlock();
  }
};

TEST( Thread, virtualFunctionCallErrorTest )
{
  static const int THREAD_CNT = 1000;
  int oldLevel = getLog()->level;
  getLog()->level = VLog::LEVEL_NONE;
  for (int i = 0; i < THREAD_CNT; i++)
  {
    NoDestructorThread* thread = new NoDestructorThread;
    thread->open();
    // Deleting object witheout calling call() medhod can occur virtual function call error.
    delete thread;
  }
  getLog()->level = oldLevel;
  LOG_INFO("THREAD_CNT=%d succeedCnt=%d virtual function call count=%d\n", THREAD_CNT, succeedCnt, THREAD_CNT - succeedCnt);
  EXPECT_TRUE( succeedCnt != THREAD_CNT ); // May be at lease one error occurs!!!
}

TEST( Thread, freeOnTerminateTest )
{
  static const int COUNT = 5;
  for (int i = 0; i < COUNT; i++)
  {
    MyThread* myThread = new MyThread(i);
    myThread->freeOnTerminate = true;
    EXPECT_TRUE( myThread->open() );
  }
  sleep(1);
}

#endif // GTEST
