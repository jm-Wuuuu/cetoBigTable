#include "cetoMemTableSL.hpp"
#include "cetoCoding.hpp"
namespace ceto
{
    #define SEQUENCENUM_AND_VALTYPE_LEN     8

    // value type
    enum ENUM_VALUE_TYPE
    {
        ENUM_VALUE_TYPE_ADD = 0x0,
        ENUM_VALUE_TYPE_DEL = 0x1,
    };

    QueryKey::QueryKey(const BinData&userKey, UINT64 sequenceNumber,
                        ValueType type)
    {
        size_t userKeyLen = userKey.len();
        size_t bufLen = userKeyLen + VARINT32_MAX_LEN +
                        SEQUENCENUM_AND_VALTYPE_LEN ;
        CHAR *dst = nullptr;
        if(len > QUERYKEY_BUF_LEN)
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
        return BinData(_userKeyStart,
                        _end - _userKeyStart - SEQUENCENUM_AND_VALTYPE_LEN );
    }

    BinData QueryKey::internalKey() const
    {
        return BinData(_userKeyStart, _end - _userKeyStart);
    }

    BinData QueryKey::memKey() const
    {
        return BinData(_memKeyStart, _end - _memKeyStart):
    }

    // MemTableSLKeyComparator implement
    INT32 MemTableSLKeyComparator::operator ()(const MemTableSLKey &lhs,
                                               const MemTableSLKey &rhs)
    {
        return BinData::compare(lhs.key, rhs.key) ;
    }

    // CetoMemTableSL implement
    CetoMemTableSL::CetoMemTableSL():_list(_allocator)
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
        UINT64
        CHAR* p = NULL;
        CHAR* newKey = _allocator.alloc(buffSize);
        if(nullptr == newKey)
        {
            return STATUS_OOM;
        }
        CHAR* p = encodeVarInt32(newKey, internalKeySize);
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
        INTELNALLIST::Iterator itr = _list.find(key.internalKey());
        CHAR* buf = itr.key();
        //TODO: extrace value
        return STATUS_OK;
    }
}