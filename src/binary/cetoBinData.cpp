#include "cetoBinData.hpp"
#include <cstring>
using std::strlen;
namespace ceto
{
    BinData::BinData():_buf(nullptr), _len(0)
    {
    }

    BinData::BinData(CHAR* buff, size_t bufLen):_buf(buff), _len(bufLen)
    {
    }

    BinData::BinData(CHAR* str):_buf(str), _len(strlen(str))
    {
    }

    BOOLEAN BinData::operator <(const BinData& rhs)
    {
        return compare(*this, rhs) > 0;
    }

    INT32 BinData::compare(const BinData& lhs, const BinData& rhs)
    {
        size_t leftLen = lhs.len();
        size_t rightLen = rhs.len();
        const CHAR* leftBuf = lhs.data();
        const CHAR* rightBuf = rhs.data();
        UINT32 minLen = leftLen > rightLen ? leftLen: rightLen;
        INT16 result = 0;

        // Compare each char
        for(UINT32 index = 0; index < minLen; index++)
        {
            result = leftBuf[index] - rightBuf[index] ;
            if(result > 0)
            {
                return 1;
            }
            else if(result < 0)
            {
                return -1;
            }
        }

        // Compare len
        if(leftLen > rightLen)
        {
            return 1;
        }
        else if(rightLen > leftLen)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}
