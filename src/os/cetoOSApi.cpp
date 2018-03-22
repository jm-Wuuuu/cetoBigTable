#include "cetoOSApi.hpp"
#include <sys/syscall.h>
namespace ceto
{
    INT32 getTID()
    {
        return static_cast< INT32 >(syscall(224));
    }
}
