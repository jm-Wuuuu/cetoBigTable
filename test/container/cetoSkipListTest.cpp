#include "gtest.h"
#include "cetoSkipList.hpp"
#include "cetoMemTableSL.hpp"
#include "cetoMemAllocator.hpp"
using namespace testing;
using namespace ceto;

class CetoSkipListTest: public Test
{
public:
    CetoSkipListTest(): list( &allocator )
    {
    }
protected:

    void SetUp()
    {
        Test::SetUp();
    }

    void TearDown()
    {
        Test::TearDown();
    }
    MemAllocator allocator ;
    SkipList< MemTableSLKey, MemAllocator, MemTableSLKeyComparator > list;
};

TEST_F( CetoSkipListTest, listinsert )
{
    MemTableSLKey key
    list.insert();
    Iterator itr = list.begin();
    while( itr != list.end() )
    {
        cout <<
    }
}