#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoTypes.hpp"
#include "cetoBinData.hpp"
#include "cetoMemMonitor.hpp"
#include "cetoRandomGenerator.hpp"
#include "cetoDebug.hpp"
#include <atomic>

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
        class Node
        {
		public:
			explicit Node( const KeyType& key );
	    	Node* next( INT32 position ) const;
			void setNext( INT32 position, Node* next );
			const KeyType& getKey() const;
		private:
            KeyType const key;
            std::atomic< Node* > forward[1];
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
        std::atomic< INT32 > _maxHeight;
    private:
        INT32 getRandomHeight() const;
        Node* findLessThan( const KeyType &key ) const;
        Node* findGreaterOrEqual( const KeyType &key ) const;
		INT32 getMaxHeight() const;
    };

    /* Iterator implement */
    template< typename KeyType, class Comparator >
        class SkipList::Iterator::Iterator( const SkipList *list ):
        _list( list ), _node( nullptr )
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
        return nullptr == this->_node ;
    }

    template< typename KeyType, class Comparator >
        const KeyType& class SkipList::Iterator::key()
    {
        return nullptr == this->_node ;
    }

	template< typename KeyType, class Comparator >
        void class SkipList::Iterator::next()
    {
    	cetoAssert( this->valid(), "Node must be valid" );
        this->_node = this->_node->next(0);
    }

	template< typename KeyType, class Comparator >
        void class SkipList::Iterator::prev()
    {
        this->_node = this->_list->findLessThan( this->_node->getKey() );
		if( this->_node == this->_list->_head )
		{
			this->_node = nullptr;
		}
    }

	template< typename KeyType, class Comparator >
        void class SkipList::Iterator::seek( const KeyType &key )
    {
        this->_node = this->_list->findGreaterOrEqual( this->_node->getKey() );
    }
}
#endif
