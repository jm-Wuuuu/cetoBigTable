#include "cetoMemAllocator.hpp"
#include "cetoDebug.hpp"
#include <stdlib.h>
namespace ceto
{
    CHAR* MemAllocator::alloc( UINT32 byte )
    {
        return static_cast<CHAR*>( malloc( byte ) );
    }

    void MemAllocator::release( void* buffer )
    {
        free( buffer );
    }
}
