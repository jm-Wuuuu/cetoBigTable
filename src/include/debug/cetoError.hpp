#ifndef CETO_ERROR_HPP
#define CETO_ERROR_HPP

namespace ceto
{
    enum STATUS
    {
        STATUS_OK = 0,
        STATUS_EXIST_KEY = -1,
        STATUS_NOTEXIST_KEY = -2,
        STATUS_OOM = -3,
        STATUS_INVALIAD_KEY = -4,
        STATUS_MAX = -1024
    };
}
#endif
