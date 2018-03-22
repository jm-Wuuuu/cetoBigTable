#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"
#include "cetoError.hpp"
namespace ceto
{
    struct BinData
    {
        BinData();
        BinData(size_t len, CHAR* buf);
        BinData(CHAR* str);
        size_t len()
        {
            return _len;
        }
        CHAR* data()
        {
            return _buf;
        }
        static INT32 compare(const BinData& lhs, const BinData& rhs) ;
        BOOLEAN operator <(const BinData& rhs) ;

    private:
        size_t _len;
        CHAR* _buf;
    };

}
#endif
