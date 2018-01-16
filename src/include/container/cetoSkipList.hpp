#ifndef CETO_SKIP_LIST_HPP
#define CETO_SKIP_LIST_HPP
#include "cetoType.hpp"
#include "cetoBinData.hpp"
#include "cetoMemAllocator.hpp"
#include "cetoRandomGenerator.hpp"
#include "cetoDebug.hpp"
#include "cetoError.hpp"
#include "ceto.hpp"
#include <atomic>
using std::atomic;
namespace ceto
{
    // SkipList define
    template< typename KeyType,
              typename Allocator,
              typename Comparator = std::less< KeyType >,
              INT32 MAXHEIGHT = 12 >
    class SkipList: public CetoObject
    {
    public:
        /* forward declaration */
        class Iterator;

        /* function declaration */
        explicit SkipList( Allocator *allocator );
        ~SkipList();
        STATUS insert( const KeyType &key );
        Iterator find( const KeyType &key );
        Iterator begin();
        Iterator end();
    public:
        /* Node declaration */
        class Node
        {
        public:
            explicit Node( const KeyType& key );
            Node* next( INT32 position ) const;
            void setNext( INT32 position, Node* next );
            const KeyType& getKey() const;
            Node* nextWithNoBarrier( INT32 position ) const;
            void setNextWithNoBarrier( INT32 position, Node* next );
        private:
            KeyType const _key;
            std::atomic< Node* > _forward[1];
        };

        /* Iterator declaration */
        class Iterator
        {
        public:
            explicit Iterator( const SkipList *list );
            explicit Iterator( const Iterator &itr );
            explicit Iterator( const SkipList *list,
                               Node* node );
            BOOLEAN valid() const;
            const KeyType& key();
            void next();
            void prev();
            void seek( const KeyType &key );
            void seekToBegin();
            void seekToEnd();
            Node& operator *() const;
            Node* operator ->() const;
            Iterator& operator =( const Iterator &itr ) const;
            BOOLEAN operator ==( const Iterator &itr ) const;
        private:
            Node *_node;
            const SkipList *_list;
        };
    private:
        Node* const _head;
        Node* const _end;
        Comparator _comparator;
        Allocator *_memAlloctor;
        RandomGenerator _random;
        std::atomic< INT32 > _maxHeight;
    private:
        INT32 _getRandomHeight() const;
        Node* _findLessThan( const KeyType &key ) const;
        Node* _findGreaterOrEqual( const KeyType &key, Node** prev ) const;
        INT32 _getMaxHeight() const;
        Node* _newNode( const KeyType &key, INT32 height );
        BOOLEAN _keyIsAfterNode( const KeyType &key, Node* node ) const;

        inline BOOLEAN _equal(  const KeyType &lhs,  const KeyType &rhs )
        {
            return ( _comparator( lhs, rhs ) == 0 );
        }
    };

    /* Skiplist implement */
    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        SkipList( Allocator *allocator ):
        _head( _newNode( KeyType(), MAXHEIGHT ) ), _end( nullptr ),
        _memAlloctor( allocator ), _maxHeight( 1 )
    {
        for( UINT32 index = 0; index < MAXHEIGHT; index++ )
        {
            _head->setNext( index, _end );
        }
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        ~SkipList()
    {
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        STATUS SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        insert( const KeyType &key )
    {
        INT32 rc = STATUS_OK;
        INT32 height = _getRandomHeight();
        Node *prev[MAXHEIGHT];
        Node *next = _findGreaterOrEqual( key, &prev );
        Node *newNode = nullptr;
        if( next != _end && _equal( next->getKey(), key ) )
        {
            rc = STATUS_EXIST_KEY;
            goto error;
        }
        if( height > _getMaxHeight() )
        {
            for( UINT32 index = _getMaxHeight(); index < height; index++ )
            {
                prev[index] = _head;
            }
            _maxHeight.store( height, std::memory_order_relaxed );
        }
        newNode = _newNode( key, height );
        for( UINT32 index = 0; index < height; index++ )
        {
            newNode->setNextWithNoBarrier( index, prev[index]->nextWithNoBarrier(index));
            prev[index]->setNext( index, newNode );
        }
    done:
        return rc;
    error:
        goto done;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        find( const KeyType &key )
    {
        Node* prev[ MAXHEIGHT ];
        Node* node = _findGreaterOrEqual( key, prev );
        return Iterator( this, node );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::begin()
    {
        Iterator itr( this, this->_head );
        return itr;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::end()
    {
        Iterator itr( this, this->_end );
        return itr;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        INT32 SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _getRandomHeight() const
    {
        const INT32 KBRANCHING = 4;
        INT32 height = 1;
        Node *prevNode = nullptr;
        while( height < MAXHEIGHT && 0 == _random() % KBRANCHING )
        {
            height++;
        }
        cetoAssert( ( height > 0 && height < this->MAXHEIGHT ),
                    "height must greater than 0 and less than MAXHEIGHT" );
        return height;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _findLessThan( const KeyType &key ) const
    {
        Node *node = _head ;
        INT32 level = _getMaxHeight() - 1;
        while( true )
        {
            cetoAssert( node == _head || _comparator( node->key, key ) < 0,
                         "node must be head node or less than key" );
            Node *next = node->next( level );
            if( next == _end || _comparator( next->key, key ) >= 0 )
            {
                if( 0 == level )
                {
                    return node;
                }
                else
                {
                    level--;
                }
            }
            else
            {
                node = next;
            }
        }
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _findGreaterOrEqual( const KeyType &key, Node** prev ) const
    {
        Node *node = _head ;
        INT32 level = _getMaxHeight() - 1;
        while( true )
        {
            Node *next = node->next( level );
            if( _keyIsAfterNode( key, next ) )
            {
                // continue to search node
                node = next;
            }
            else
            {
                if( prev != nullptr )
                {
                    prev[level] = node;
                }

                // the lowest level, need to return next node
                if( 0 == level )
                {
                    return next;
                }
                else
                {
                    // current level no exist node, need to search lower level
                    level--;
                }
            }
        }
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        INT32 SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _getMaxHeight() const
    {
        return _maxHeight.load( std::memory_order_relaxed );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _newNode( const KeyType &key, INT32 height )
    {
        char *mem = _memAlloctor->alloc( sizeof(Node) +
                    sizeof(std::atomic< Node* >) * (height - 1) );
        return new (mem) Node(key);
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        BOOLEAN SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        _keyIsAfterNode( const KeyType &key, Node* node ) const
    {
        cetoAssert( node != nullptr, "node must not be nullptr" );
        return ( node != _end &&
                  ( _comparator( node->getKey(), key ) < 0 ) );
    }
    /* Node implement */
    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node::
        Node( const KeyType& key ): _key( key )
    {
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node::
        next( INT32 position ) const
    {
        return this->_forward[ position ].load( std::memory_order_acquire );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node::
        setNext( INT32 position, Node* next )
    {
        this->_forward[ position ].store( next, std::memory_order_release );
    }


    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node::
        nextWithNoBarrier( INT32 position ) const
    {
        return this->_forward[ position ].load( std::memory_order_relaxed );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node::
        setNextWithNoBarrier( INT32 position, Node* next )
    {
        this->_forward[ position ].store( next, std::memory_order_relaxed );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        const KeyType& SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::
        Node::getKey() const
    {
        return this->_key;
    }

    /* Iterator implement */
    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        Iterator( const SkipList *list ): _list( list ), _node( nullptr )
    {
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        Iterator( const Iterator &itr ): _list( itr._list ), _node( itr._node )
    {
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        Iterator( const SkipList *list, Node* node ):
            _list( list ), _node( node )
    {
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        BOOLEAN SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        valid() const
    {
        return nullptr == this->_node ;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        const KeyType&
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::key()
    {
        return this->_node->getKey();
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        next()
    {
        cetoAssert( this->valid(), "Node must be valid" );
        this->_node = this->_node->next(0);
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        prev()
    {
        this->_node = this->_list->findLessThan( this->_node->getKey() );
        if( this->_node == this->_list->_head )
        {
            this->_node = nullptr;
        }
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        seek( const KeyType &key )
    {
        this->_node = this->_list->findGreaterOrEqual( this->_node->getKey() );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        seekToBegin()
    {
        this->_node = this->_list->_head->next( 0 );
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        void SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        seekToEnd()
    {
        this->_node = this->_list.end()._node;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node&
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        operator *() const
    {
        return *(this->_node ) ;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Node*
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        operator ->() const
    {
        return this->_node;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        typename SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator&
        SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        operator =
        ( const Iterator &itr ) const
    {
        this->_node = itr._node;
        this->_list = itr._list;
        return *this;
    }

    template< typename KeyType, typename Allocator,
        typename Comparator, INT32 MAXHEIGHT >
        BOOLEAN SkipList< KeyType, Allocator, Comparator, MAXHEIGHT >::Iterator::
        operator ==( const Iterator &itr ) const
    {
        return this->_node == itr._node && this->_list == itr._list;
    }
}
#endif
