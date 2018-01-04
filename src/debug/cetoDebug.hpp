#ifndef CETO_DEBUG_HPP
#define CETO_DEBUG_HPP
#include "cetoType.hpp"
namespace ceto
{

    static _cetoPanic()
    {
        INT32 *ptr = NULL;
        *ptr = 10;
    }
#if defined(CETO_CLIENT)
    inline void cetoAssert( cond, str )
    {
        assert( cond );
    }
#elif defined(CETO_SERVER)
    inline void cetoAssert( cond, str )
    {
        if( !cond )
        {

        }
        _cetoPanic();
    }
#endif
}
#endif
