#ifndef CETO_MEM_TABLE_SL_HPP
#define CETO_MEM_TABLE_SL_HPP
#include "cetoSkipList.hpp"
#include "cetoMemAllocator.hpp"
#include "cetoMemTable.hpp"
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
        INT32 operator ()( const MemTableSLKey &lhs, const MemTableSLKey &rhs );
    };

    // CetoMemTableSL define
    class CetoMemTableSL: public CetoMemTable
    {
    public:
        CetoMemTableSL();
        ~CetoMemTableSL();
        virtual STATUS init();
        virtual STATUS insert( const BinData& key, const BinData& value );
        virtual STATUS query( const BinData& key, BinData& value );
    private:
        SkipList< MemTableSLKey, MemAllocator, MemTableSLKeyComparator > _list;
    };
}
#endif