#ifndef CETO_LOG_HPP
#define CETO_LOG_HPP
#include <stdarg.h>
#include <mutex>
#include <unistd.h>
#include "cetoError.hpp"
namespace ceto
{
    /* Api */
    inline void LOG_INIT( const string filename, LOG_LEVEL level = DEFAULT );
    inline void CETOLOG( LOG_LEVEL level, const *fmt, ... );

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

    class LogSingleton
    {
    public:
        ~LogSingleton();
        void writeLog( LOG_LEVEL level, const CHAR* fmt, va_list ap );

        inline void setLogLevel( LOG_LEVEL level )
        {
            _level = level;
        }
        inline void setLogFileName( const string &filename )
        {
            _filename = filename ;
        }
        inline const string& getLogFileName()
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
        string _filename;
        LOG_LEVEL _level;
        std::mutex _mutex;
        static const CHAR *_levelStr[5] = { "SERIOUS", "ERROR",
                                            "EVENT", "INFO", "DEBUG" };

    };

    LogSingleton& getCetoLog()
    {
        return LogSingleton::singleton;
    }

    inline void LOG_INIT( const string filename, LOG_LEVEL level )
    {
        LogSingleton& logObj = getCetoLog();
        logObj.setLogFileName( filename );
        logObj.setLogLevel( level );
        if( access( filename, F_OK ) )
        {
            if( mkdir( LOG_PATH, S_IRWXU | S_IRWXG ) )
            {
                printf( "Failed to create dir log\n" );
            }
        }
    }

    inline void CETOLOG( LOG_LEVEL level, const CHAR* fmt, ... )
    {
        va_list ap;
        va_start( ap, fmt );
        getCetoLog().writeLog( level, fmt, ap );
        va_end( ap );
    }

    // TODO
    inline TEST_RESULT( BOOLEAN condition, STATUS retCode, const CHAR* fmt, ... );
}
#endif
