#ifndef CETO_MEM_TABLE_SL_HPP
#define CETO_MEM_TABLE_SL_HPP
#include "cetoSkipList.hpp"
#include "cetoMemAllocator.hpp"
#include "cetoMemTable.hpp"
namespace ceto
{
    enum ValueType
    {
        ENUM_TYPE_ADD = 0x0,
        ENUM_TYPE_DEL = 0x1,
    };



    // CetoMemTableSL define
    class CetoMemTableSL: public CetoMemTable
    {
    public:
        typedef CHAR* KeyType;

        // MemTableSLKeyComparator define
        struct MemTableSLKeyComparator
        {
            INT32 operator ()( const KeyType &lhs, const KeyType &rhs );
        };
        CetoMemTableSL();
        ~CetoMemTableSL();
        virtual STATUS insert( UINT64 sequenceNumber,
                               const BinData& key, ValueType type,
                               const BinData& value );
        virtual STATUS query( const BinData& key, BinData& value );
    private:
        MemAllocator _allocator;
        SkipList< KeyType, MemAllocator, MemTableSLKeyComparator > _list;
    };
}
#endif