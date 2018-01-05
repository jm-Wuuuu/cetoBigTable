#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"

namespace ceto
{
    struct BinData
    {
        UINT32 len;
        CHAR buf[1];
        static INT32 compare( const BinData& lhs, const BinData& rhs ) ;
    };

}
#endif
