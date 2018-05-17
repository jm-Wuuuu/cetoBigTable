#include "gtest.h"
#include "cetoBinData.hpp"
using namespace testing;
using namespace ceto;

class CetoBinDataTest: public Test
{
public:
    CetoBinDataTest()
    {
    }
protected:

    virtual void SetUp()
    {
        Test::SetUp();
    }

    virtual void TearDown()
    {
        Test::TearDown();
    }
};

TEST_F( CetoBinDataTest, InitAndGetData )
{
    {
        BinData data;
        ASSERT_TRUE(0 == data.len()) << "Default constructor function len must be 0";
        ASSERT_TRUE(nullptr == data.data()) << "Default constructor function data must be nullptr";
    }
    {
        BinData data( "str" );
        const CHAR* buf = data.data();
        ASSERT_TRUE(3 == data.len()) << "Len must be 0";
        ASSERT_TRUE('s' == buf[0] && 't' == buf[1] && 'r' == buf[2]) 
            << "Data must be \"str\"";
    }
    {
        BinData data( "hello", 5 );
        const CHAR* buf = data.data();
        ASSERT_TRUE(5 == data.len())
            << "Len must be 0";
        ASSERT_TRUE('h' == buf[0] && 'e' == buf[1] && 'l' == buf[2] &&
                    'l' == buf[3] && 'o' == buf[4])
            << "Data must be \"str\"";
    }
}

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}