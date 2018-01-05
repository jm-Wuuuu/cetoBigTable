#include "cetoMemTableSL.hpp"

namespace ceto
{
    // MemTableSLKeyComparator implement
    INT32 MemTableSLKeyComparator::perator ()( const MemTableSLKey &lhs,
                                               const MemTableSLKey &rhs )
    {
        return BinData::compare( lhs.key, rhs.key ) ;
    }

    // CetoMemTableSL implement
    STATUS CetoMemTableSL::init()
    {
        return STATUS_OK;
    }

    STATUS CetoMemTableSL::insert( const BinData& key, const BinData& value )
    {
    }

    STATUS CetoMemTableSL::query( const BinData& key, BinData& value )
    {
    }
}