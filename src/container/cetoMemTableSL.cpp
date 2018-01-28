#include "cetoMemTableSL.hpp"

namespace ceto
{
    typedef UINT64 SequenceNumber ;
    // value type
    enum ENUM_VALUE_TYPE
    {
        ENUM_VALUE_TYPE_ADD = 0x0,
        ENUM_VALUE_TYPE_DEL = 0x1,
    };

    // MemTableSLKeyComparator implement
    INT32 MemTableSLKeyComparator::operator ()( const MemTableSLKey &lhs,
                                               const MemTableSLKey &rhs )
    {
        return BinData::compare( lhs.key, rhs.key ) ;
    }

    // CetoMemTableSL implement
    CetoMemTableSL::CetoMemTableSL():_list( &getMemAllocator() )
    {
    }

    STATUS CetoMemTableSL::init()
    {
        return STATUS_OK;
    }

    STATUS CetoMemTableSL::insert( SequenceNumber, const BinData& key, const BinData& value )
    {
        return STATUS_OK;
    }

    STATUS CetoMemTableSL::query( const BinData& key, BinData& value )
    {
        return STATUS_OK;
    }
}