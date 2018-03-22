#ifndef CETO_CODING_HPP
#define CETO_CODING_HPP
#include "cetoType.hpp"
namespace ceto
{
    #define VARINT32_MAX_LEN    5
    size_t getVarIntLength(UINT64 length);

    size_t getVarIntLength(UINT32 length);

    CHAR* encodeVarInt32(CHAR* buf, UINT32 len);

    CHAR* encodeInt32(CHAR* buf, UINT32 val);

    CHAR* encodeInt64(CHAR* buf, UINT64 val);
}
#endif
