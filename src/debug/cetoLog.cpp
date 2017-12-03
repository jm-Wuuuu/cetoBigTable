#include "cetoLog.hpp"
#include "cetoOSApi.hpp"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
using namespace std;
namespace ceto
{
    const INT32 CETO_LOGMSG_MAX_LEN = 1024*1024;
    #define   CETO_LOG_FORMAT     " PID: %-15d\tTID: %-15d\n LEVEL: %s\tFILE: %-14s\n FUNCTION: %s\tLINE: %-14d\n TIME: %s\n %s\n\n\n"
    /* init static variable */
    LogSingleton::singleton;

    LogSingleton::~LogSingleton()
    {
    }

    LogSingleton::LogSingleton(): _level( DEFAULT )
    {
    }

    void LogSingleton::writeLog( LOG_LEVEL level, const CHAR* fmt, va_list ap )
    {
        if( level > _level )
        {
            return;
        }
        CHAR msg[ CETO_LOGMSG_MAX_LEN ];
        bool logToStdout = _filename.empty();
        FILE *fp = NULL;
        CHAR buf[ 1024 ];

        va_start( ap, fmt );                                                \
        vsnprintf( msg, sizeof( msg ), fmt, ap );                           \
        va_end( ap );

        {
            std::lock_guard<std::mutex> lock( _mutex );
            fp = logToStdout ? stdout :
                               fopen( CetoLog::getLogFile().c_str(), "a" );
            // Failed to open file
            if( !fp )
            {
                return;
            }

            if( RAW == level )
            {
                fprintf( fp, "%s", msg );
            }
            else
            {
                INT32 off;
                time_t lt;
                lt =time(NULL);
                strftime( buf, sizeof( buf ), "%d %b %H:%M:%S", localtime( &lt ) );
                fprintf( fp, CETO_LOG_FORMAT, ( INT32 )getpid(), getTID,
                         _levelStr[ level ], basename( __FILE__ ),
                         __FUNCTION__, __LINE__, buf, msg );

            }
            fflush( fp );

            if( !logToStdout )
            {
                fclose( fp );
            }
        }
    }
}
