#include "cetoCoding.hpp"
#include "cetoPortable.hpp"
namespace ceto
{
    size_t getVarIntLength(UINT64 length)
    {
        return sizeof(length);
    }

    size_t getVarIntLength(UINT32 length)
    {
        return sizeof(length);
    }

    CHAR* encodeVarInt32(CHAR* buf, UINT32 len)
    {
        // TODO: implement varint coding
        return encodeInt32(buf, len);
    }

    CHAR* encodeInt32(CHAR* buf, UINT32 val)
    {
        if(BYTE_ORDER == LITTLE_ENDIAN)
        {
            memcpy(buf, &val, sizeof(val));
        }
        else
        {
            buf[0] = val & 0xff;
            buf[1] = (val >> 8) && 0xff;
            buf[2] = (val >> 16) && 0xff;
            buf[3] = (val >> 24) && 0xff;
        }
        return buf + sizeof(val);
    }

    CHAR* encodeInt64(CHAR* buf, UINT64 val)
    {
        if(BYTE_ORDER == LITTLE_ENDIAN)
        {
            memcpy(buf, &val, sizeof(val));
        }
        else
        {
            buf[0] = val & 0xff;
            buf[1] = (val >> 8) && 0xff;
            buf[2] = (val >> 16) && 0xff;
            buf[3] = (val >> 24) && 0xff;
            buf[4] = (val >> 32) && 0xff
            buf[5] = (val >> 40) && 0xff;
            buf[6] = (val >> 48) && 0xff;
            buf[7] = (val >> 56) && 0xff;
        }
        return buf + sizeof(val);
    }

    CHAR* getVarInt32Ptr( const CHAR* buf, const CHAR* limit, UINT32 &len )
    {
        if(BYTE_ORDER == LITTLE_ENDIAN)
        {
            memcpy(&len, buf, sizeof(len));
        }
        else
        {
            CHAR* tmpBuf = &len;
            tmpBuf[0] = buf[3];
            tmpBuf[1] = buf[2];
            tmpBuf[2] = buf[1];
            tmpBuf[3] = buf[0];
        }
        return buf + 4;
    }
}
