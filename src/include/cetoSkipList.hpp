#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoTypes.hpp"
#include "cetoBinData.hpp"
#include "cetoMemMonitor.hpp"
#include "cetoRandomGenerator.hpp"
#include "cetoBarrier.hpp"
namespace ceto
{
    // SkipList define
    template< typename KeyType,
              typename Comparator = std::less< KeyType >,
              typename Allocator,
              INT32 MAXHEIGHT = 12 >
    class SkipList
    {
    public:
        /* forward declaration */
        class Iterator;

        /* function declaration */
        explicit SkipList();
        ~SkipList();
        std::pair< Iterator, INT32 > insert( const KeyType &key );
        Iterator find( const KeyType &key );
        Iterator begin();
        Iterator end();
    public:
        /* Node declaration */
        template< typename KeyType, typename compareFunc >
        struct Node
        {
            KeyType key;
            Node* forward[1];
        };

        /* Iterator declaration */
        class Iterator
        {
        public:
            explicit Iterator( const SkipList *list );
            explicit Iterator( const Iterator &itr );
            BOOLEAN valid() const;
            const KeyType& key();
            void next();
            void prev();
            void seek( const KeyType &key );
            void seekToBegin();
            void seekToEnd();
            Node& operator *() const;
            Node* operator ->() const;
            Iterator operator =() const;
        private:
            Node *_node;
            const SkipList *_list;
        };
    private:
        Node* const _head;
        Comparator _comparator;
        Allocator _memAlloctor;
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
