#ifndef CETO_MEM_TABLE_SL_HPP
#define CETO_MEM_TABLE_SL_HPP
#include "cetoSkipList.hpp"
namespace ceto
{
    struct SLKey
    {
        BinData key;
        BinData value;
    };

    struct SLKeyComparator
    {
        INT32 operator ()( const SLKey &lhs, const SLKey &rhs )
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
    };
    class CetoMemTableSL: CetoMemTable
    {
    public:
        virtual Status init();
        virtual Status insert( const BinData& key, const BinData& value );
        virtual Status query( const BinData& key, BinData& value );
    private:
        SkipList< SLKey,SLKeyComparator > _list;
    };
}
#endif