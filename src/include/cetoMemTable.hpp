#ifndef CETO_MEM_TABLE_HPP
#define CETO_MEM_TABLE_HPP
#include "cetoError.hpp"
#include "cetoBinData.hpp"
namespace ceto
{
    class CetoMemTable
    {
    public:
        virtual Status init() ;
        virtual Status insert( const BinData& key, const BinData& value ) = 0;
        virtual Status query( const BinData& key, BinData& value ) = 0;
    };
}
#endif
