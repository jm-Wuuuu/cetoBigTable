#ifndef CETO_DEBUG_HPP
#define CETO_DEBUG_HPP
#include "cetoType.hpp"
namespace ceto
{

    static void _cetoPanic()
    {
        INT32 *ptr = NULL;
        *ptr = 10;
    }
#if defined(CETO_CLIENT)
    inline void cetoAssert( BOOLEAN cond, const CHAR* str )
    {
        assert( cond );
    }
#elif defined(CETO_SERVER)
    inline void cetoAssert( BOOLEAN cond, const CHAR* str )
    {
        if( !cond )
        {

        }
        _cetoPanic();
    }
#endif
}
#endif
