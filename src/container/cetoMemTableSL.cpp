#include "cetoMemTableSL.hpp"

namespace ceto
{
    // MemTableSLKeyComparator implement
    INT32 MemTableSLKeyComparator::perator ()( const SLKey &lhs, const SLKey &rhs )
    {
        INT32 ret = 0;
        INT32 length = -1 ;
        const CHAR* lBuffer = lhs.key.buf;
        const CHAR* rBuffer = rhs.key.buf;
        ret = lhs.key.len - rhs.key.len;
        length = lhs.key.len < rhs.key.len? lhs.key.len: rhs.key.len;

        for( UINT32 index = 0; index < length; index++ )
        {
            INT32 tmp = lBuffer[index] - rBuffer[index];
            if( tmp )
            {
                return tmp
            }
        }
        return ret;
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
    }

    STATUS CetoMemTableSL::query( const BinData& key, BinData& value )
    {
    }
}