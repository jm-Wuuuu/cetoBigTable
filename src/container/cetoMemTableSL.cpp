#include "cetoMemTableSL.hpp"

namespace ceto
{
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

    STATUS CetoMemTableSL::insert( const BinData& key, const BinData& value )
    {
        return STATUS_OK;
    }

    STATUS CetoMemTableSL::query( const BinData& key, BinData& value )
    {
        return STATUS_OK;
    }
}