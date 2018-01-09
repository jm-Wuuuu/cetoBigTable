#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"
#include "cetoError.hpp"
namespace ceto
{
    struct BinData
    {
        static STATUS newBinData( UINT32 len, CHAR*buf );
        UINT32 len;
        CHAR buf[1];
        static INT32 compare( const BinData& lhs, const BinData& rhs ) ;
    };

}
#endif
