#ifndef CETO_OPTIONS_HPP
#define CETO_OPTIONS_HPP

#include "ceto.hpp"

namespace ceto
{
    class CetoOptions: public cetoObject
    {
    public:
        CetoOptions();
        ~CetoOptions();

        INT32 init();



        INT32 getDialogLevel()
        {
            return _dialogLevel;
        }
    private:
        INT32 _dialogLevel ;
    };
}

#endif
