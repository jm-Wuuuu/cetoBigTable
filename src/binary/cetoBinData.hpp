#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"
#include "cetoError.hpp"
namespace ceto
{
    struct BinData
    {
<<<<<<< HEAD
        static STATUS newBinData( UINT32 len, CHAR*buf );
=======
>>>>>>> c71911c37d62758d28a5a41ed4e1a2dfbb265acd
        UINT32 len;
        CHAR buf[1];
        static INT32 compare( const BinData& lhs, const BinData& rhs ) ;
    };

}
#endif
