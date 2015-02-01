#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>
#include <VDependency>

class Log
{
private:
  Log()          { printf("Log::Log\n");  }
  virtual ~Log() { printf("Log::~Log\n"); }
public:
  static Log& instance()
  {
    static Log log;
    return log;
  }
  void write(const char* msg)
  {
    printf("%s\n", msg);
  }
  static void dependency()
  {
    instance();
  }
};

class App : public VDependency<Log>
{
private:
  App()          { Log::instance().write("App::App");  }
  virtual ~App() { Log::instance().write("App::~App"); }
public:
  static App& instance()
  {
    static App app;
    return app;
  }
  void foo()
  {
    Log::instance().write("App::foo");
  }
};

TEST( Design, dependencyTest )
{
  //
  // App instance is called first in main application,
  // but Log instance must be initialized before App instance is initialized.
  //
  App::instance().foo();
  App::instance();
}

#endif // GTEST
