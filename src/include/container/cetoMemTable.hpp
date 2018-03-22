#ifndef CETO_MEM_TABLE_HPP
#define CETO_MEM_TABLE_HPP
#include "cetoError.hpp"
#include "cetoBinData.hpp"
#include "ceto.hpp"
namespace ceto
{
    class CetoMemTable: public CetoObject
    {
    public:
        virtual STATUS init() = 0;
        virtual STATUS insert(const BinData& key, const BinData& value) = 0;
        virtual STATUS query(const BinData& key, BinData& value) = 0;
    };
}
#endif
