#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoBinData.hpp"
#include "cetoMemMonitor.hpp"
#include "cetoRandomGenerator.hpp"
namespace ceto
{
    // List define
    template< typename KeyType, class Comparator >
    class SkipList
    {
    public:
        explicit SkipList();
        ~SkipList();

        insert( const KeyType &key );
        exist( const KeyType &key );
    public:
        template< typename KeyType, typename compareFunc >
        struct Node
        {
            KeyType key;
            Node* forward[1];
        };

        class Iterator
        {
        public:
            explicit Iterator( const SkipList *list );
            BOOLEAN valid();
            const KeyType& key();
            void next();
            void prev();
            void seek( const KeyType &key );
            void seekToBegin();
            void seekToEnd();
        private:
            Node *_node;
            const SkipList *_list;
        };
    private:
        const INT32 RANDOM_HIGHT_MAX = 12;
        Node* const _head;
        Comparator _comparator;
        MemMonitor _memMonitor;
        RandomGenerator _random;
        //TODO: Add Atomic type _maxHeight
    private:

        INT32 getRandomHeight();
        Node* findLessThan( const KeyType &key );
        Node* findGreaterOrEqual( const KeyType &key );
    };
}
#endif
