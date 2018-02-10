include "cetoBinData.hpp"

namespace ceto
{
    BinData::BinData(): len( 0 ), buf( nullptr )
    {
    }

    BinData::BinData( UINT32 bufLen, CHAR* buff ): len( bufLen ), buf( buff )
    {
    }

    BinData::BinData( CHAR* str ): len( strlen( str ) ), buf( str )
    {
    }

    BOOLEAN BinData::operator <( const BinData& rhs )
    {
        return compare( *this, rhs ) > 0;
    }

    INT32 BinData::compare( const BinData& lhs, const BinData& rhs )
    {
        UINT32 leftLen = lhs.len;
        UINT32 rightLen = rhs.len;
        const CHAR* leftBuf = &lhs.buf;
        const CHAR* rightBuf = &rhs.buf;
        UINT32 minLen = lhs.len > rhs.len ? lhs.len: rhs.len;
        INT16 result = 0;

        // Compare each char
        for( UINT32 index = 0; index < minLen; index++ )
        {
            result = leftBuf[index] - rightBuf[index] ;
            if( result > 0 )
            {
                return 1;
            }
            else if( result < 0 )
            {
                return -1;
            }
        }

        // Compare len
        if( leftLen > rightLen )
        {
            return 1;
        }
        else if( rightLen > leftLen )
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}
