#include "cetoMemTableSL.hpp"
#include "cetoCoding.hpp"
#include "cetoLog.hpp"
#include <cstring>
namespace ceto
{
    #define SEQUENCENUM_AND_VALTYPE_LEN     8

    // value type
    enum ENUM_VALUE_TYPE
    {
        ENUM_VALUE_TYPE_ADD = 0x0,
        ENUM_VALUE_TYPE_DEL = 0x1,
    };

    QueryKey::QueryKey(const BinData& userKey, UINT64 sequenceNumber,
                       ValueType type)
    {
        size_t userKeyLen = userKey.len();
        size_t bufLen = userKeyLen + VARINT32_MAX_LEN +
                        SEQUENCENUM_AND_VALTYPE_LEN ;
        CHAR *dst = nullptr;
        if(bufLen > QUERYKEY_BUF_LEN)
        {
            _memKeyStart = new CHAR[bufLen];
        }
        else
        {
            _memKeyStart = _buf;
        }
        dst = encodeVarInt32(_memKeyStart,
                             userKeyLen + SEQUENCENUM_AND_VALTYPE_LEN);
        _userKeyStart = dst;
        memcpy(dst, userKey.data(), userKeyLen);
        dst += userKeyLen;
        dst = encodeInt64(dst, sequenceNumber << 8 | type);
        _end = dst;
    }

    BinData QueryKey::userKey() const
    {
        return BinData(_userKeyStart, _end - _userKeyStart - SEQUENCENUM_AND_VALTYPE_LEN);
    }

    BinData QueryKey::internalKey() const
    {
        return BinData(_userKeyStart, _end - _userKeyStart);
    }

    BinData QueryKey::memKey() const
    {
        return BinData(_memKeyStart, _end - _memKeyStart);
    }

    // MemTableSLKeyComparator implement
    INT32 MemTableSLKeyComparator::operator ()(const CHAR* lhs, const CHAR* rhs) const
    {
        UINT32 lhsLen = 0;
        UINT32 rhsLen = 0;
        CHAR* lhsBuf = getVarInt32Ptr(lhs, lhs + VARINT32_MAX_LEN, lhsLen);
        CHAR* rhsBuf = getVarInt32Ptr(rhs, rhs + VARINT32_MAX_LEN, rhsLen);
        return BinData::compare(BinData(lhsBuf, lhsLen),
                                BinData(rhsBuf, rhsLen));
    }

    // CetoMemTableSL implement
    CetoMemTableSL::CetoMemTableSL():_list(&_allocator)
    {
    }

    STATUS CetoMemTableSL::insert(UINT64 sequenceNumber, const BinData& key,
                                  ValueType type, const BinData& value)
    {
        STATUS stat = STATUS_OK;
        size_t keySize = key.len();
        size_t valSize = value.len();
        size_t internalKeySize = keySize + sizeof(sequenceNumber);
        size_t buffSize = getVarIntLength(internalKeySize) + internalKeySize
                          + getVarIntLength(valSize) + valSize;
        CHAR* p = nullptr;
        CHAR* newKey = _allocator.alloc(buffSize);
        if(nullptr == newKey)
        {
            return STATUS_OOM;
        }
        p = encodeVarInt32(newKey, internalKeySize);
        memcpy(p, key.data(), keySize);
        p += keySize;
        p = encodeInt64(p, sequenceNumber << 8 | type);
        p = encodeVarInt32(p, valSize);
        memcpy(p, value.data(), valSize);
        stat = _list.insert(newKey);
        if(STATUS_OK != stat)
        {
            CETOLOG(LOG_LEVEL::ERROR, "Failed to insert key, rc: %d", stat);
            return stat;
        }
        return STATUS_OK;
    }

    STATUS CetoMemTableSL::query(const QueryKey& key, BinData& value)
    {
        INTELNALLIST::Iterator itr = _list.find(key.memKey().data());
        UINT32 keyLen = 0;
        UINT32 valLen = 0;
        CHAR* buf = NULL;
        CHAR* ptr = NULL;
        if(!itr.valid())
        {
            return STATUS_INVALIAD_KEY;
        }
        buf = itr.key();
        ptr = getVarInt32Ptr(buf, buf + VARINT32_MAX_LEN, keyLen);
        ptr += keyLen;
        ptr = getVarInt32Ptr(ptr, ptr + VARINT32_MAX_LEN, valLen);
        value = BinData(ptr, valLen);
        return STATUS_OK;
    }
}