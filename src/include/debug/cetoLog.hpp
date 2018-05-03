#ifndef CETO_LOG_HPP
#define CETO_LOG_HPP
#include <stdarg.h>
#include <mutex>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cetoError.hpp"
namespace ceto
{
    /* Log level */
    enum LOG_LEVEL
    {
        RAW = 0,
        SERIOUS,
        ERROR,
        EVENT,
        INFO,
        DEBUG,
        DEFAULT = ERROR
    };

    /* Api */
    inline void LOG_INIT(const std::string filename, LOG_LEVEL level = DEFAULT);
    inline void CETOLOG(LOG_LEVEL level, const CHAR *fmt, ...);

    class LogSingleton
    {
    public:
        ~LogSingleton();
        void writeLog(LOG_LEVEL level, const CHAR* fmt, va_list ap);

        inline void setLogLevel(LOG_LEVEL level)
        {
            _level = level;
        }
        inline void setLogFileName(const std::string &filename)
        {
            _filename = filename ;
        }
        inline const std::string& getLogFileName()
        {
            return  _filename ;
        }

        inline LOG_LEVEL getLogLevel()
        {
            return _level;
        }
    public:
        static LogSingleton& singleton;
    private:
        LogSingleton();
    private:
        std::string _filename;
        LOG_LEVEL _level;
        std::mutex _mutex;
        constexpr static const CHAR *_levelStr[5] = { "SERIOUS", "ERROR",
                                                      "EVENT", "INFO", "DEBUG" };
    };

    LogSingleton& getCetoLog()
    {
        return LogSingleton::singleton;
    }

    inline void LOG_INIT(const std::string& filename, LOG_LEVEL level)
    {
        LogSingleton& logObj = getCetoLog();
        logObj.setLogFileName(filename);
        logObj.setLogLevel(level);
        if(access(filename.c_str(), F_OK))
        {
  /*          if(mkdir(LOG_PATH, S_IRWXU | S_IRWXG))
            {
                printf("Failed to create dir log\n");
            }*/
        }
    }

    inline void CETOLOG(LOG_LEVEL level, const CHAR* fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        getCetoLog().writeLog(level, fmt, ap);
        va_end(ap);
    }

    // TODO#
    inline void TEST_RESULT(BOOLEAN condition, STATUS retCode, const CHAR* fmt, ...);
}
#endif
