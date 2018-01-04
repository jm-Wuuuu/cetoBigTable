#ifndef CETO_MEM_TABLE_SL_HPP
#define CETO_MEM_TABLE_SL_HPP
#include "cetoSkipList.hpp"
namespace ceto
{
    // MemTableSLKey define
    struct MemTableSLKey
    {
        BinData key;
        BinData value;
    };

    // MemTableSLKeyComparator define
    struct MemTableSLKeyComparator
    {
        INT32 operator ()( const SLKey &lhs, const SLKey &rhs );
    };

    // CetoMemTableSL define
    class CetoMemTableSL: CetoMemTable
    {
    public:
        virtual STATUS init();
        virtual STATUS insert( const BinData& key, const BinData& value );
        virtual STATUS query( const BinData& key, BinData& value );
    private:
        SkipList< MemTableSLKey, MemTableSLKeyComparator > _list;
    };
}
#endif