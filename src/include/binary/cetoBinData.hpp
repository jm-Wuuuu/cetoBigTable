#ifndef CETO_BINDATA_HPP
#define CETO_BINDATA_HPP

#include "cetoType.hpp"
#include "cetoError.hpp"
namespace ceto
{
    struct BinData
    {
        BinData();
        BinData(CHAR* buf, size_t len);
        BinData(CHAR* str);
        size_t len() const
        {
            return _len;
        }
        CHAR* data() const
        {
            return _buf;
        }
        static INT32 compare(const BinData& lhs, const BinData& rhs) ;
        BOOLEAN operator <(const BinData& rhs) ;

    private:
        CHAR* _buf;
        size_t _len;
    };

}
#endif
