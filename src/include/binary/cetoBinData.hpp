#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"
#include "cetoError.hpp"
namespace ceto
{
    struct BinData
    {
        BinData();
        BinData( UINT32 len, CHAR* buf );
        BinData( CHAR* str );
        UINT32 len;
        CHAR *buf;
        static INT32 compare( const BinData& lhs, const BinData& rhs ) ;
        BOOLEAN operator <( const BinData& rhs ) ;
    private:
        BinData();
    };

}
#endif
