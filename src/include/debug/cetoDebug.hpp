#ifndef CETO_DEBUG_HPP
#define CETO_DEBUG_HPP
#include "cetoType.hpp"
namespace ceto
{

#ifdef _DEBUG
    inline void cetoAssert(BOOLEAN cond, const CHAR* str)
    {
        assert(cond);
    }
#else
    inline void cetoAssert(BOOLEAN cond, const CHAR* str)
    {
        if(!cond)
        {

        }
    }
#endif
}
#endif
