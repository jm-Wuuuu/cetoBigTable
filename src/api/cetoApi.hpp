#ifndef CETO_API_HPP
#define CETO_API_HPP
#include "cetoBinData.hpp"
#include <string>
using std::string;

namespace ceto
{
    enum DBMODE
    {
        DB_OPEN = 0,
        DB_CREATE = 1,
        DB_REPLACE = 2,
    }

    class DBTable
    {
    public:
        INT32 open( const string& dbName, DBMODE mode = DB_OPEN );

        INT32 insert( const BinData &key, const BinData &value );

        INT32 delete( const BinData &key );

        INT32 query( const BinData &key );

        static INT32 removeDB( const string& dbName );
    };
}
#endif
