#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoBinData.hpp"
#include "cetoMemMonitor.hpp"
#include "cetoRandomGenerator.hpp"
#include "cetoBarrier.hpp"
namespace ceto
{
    // SkipList define
    template< typename KeyType, class Comparator >
    class SkipList
    {
    public:
        explicit SkipList();
        ~SkipList();

        Iterator insert( const KeyType &key );
        Iterator find( const KeyType &key );

        Iterator begin();
        Iterator end();
    public:
        /* Node define */
        template< typename KeyType, typename compareFunc >
        struct Node
        {
            KeyType key;
            Node* forward[1];
        };

        /* Iterator define */
        class Iterator
        {
        public:
            explicit Iterator( const SkipList *list );
            explicit Iterator( Iterator itr );
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
        Barrier< INT32 > _maxHeight;
    private:
        INT32 getRandomHeight();
        Node* findLessThan( const KeyType &key );
        Node* findGreaterOrEqual( const KeyType &key );
    };

    /* Iterator implement */
    template< typename KeyType, class Comparator >
        class SkipList::Iterator::Iterator( const SkipList *list ):
        _list( list ), _node( NULL )
    {
    }

    template< typename KeyType, class Comparator >
        class SkipList::Iterator::Iterator( Iterator itr ):
            _list( itr._list ), _node( itr._node )
    {
    }

    template< typename KeyType, class Comparator >
        BOOLEAN class SkipList::Iterator::valid()
    {
        return NULL == this->_node ;
    }

    template< typename KeyType, class Comparator >
        const KeyType& class SkipList::Iterator::key()
    {
        return NULL == this->_node ;
    }
}
#endif
