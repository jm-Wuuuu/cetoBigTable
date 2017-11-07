#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoBinData.hpp"
namespace ceto
{
    // List define
    template< typename KeyType, typename compareFunc >
    class SkipList
    {
    public:
        explicit SkipList();
        ~SkipList();

        init();
    private:
        template< typename KeyType, typename compareFunc >
        struct Node
        {
            KeyType key;
            Node* forward[1];
        };
        INT32 level ;
        Node* header ;
    };
}
#endif
