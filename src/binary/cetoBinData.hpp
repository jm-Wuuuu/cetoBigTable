#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"

namespace ceto
{
    struct BinData
    {
        static newBinData( UINT32 len, CHAR*buf );
        UINT32 len;
        CHAR* buf;
    };


    INT32 compare( const BinData& lhs, const BinData& rhs );

}
#endif
