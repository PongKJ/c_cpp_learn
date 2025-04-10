#pragma once
#include <dbg.h>

#include <iostream>
#include <stdexcept>

using namespace std;

template < typename T > struct Node {
    T data;
    Node* next;
};

template < typename T > class CircularList {
private:
    Node< T >* m_head = nullptr;
    Node< T >* m_tail = nullptr;

public:
    CircularList() = default;
    ~CircularList() {
        Node< T >* p = m_head;
        while ( p != m_tail ) {
            Node< T >* q = p;
            p            = p->next;
            delete q;
        }
        delete p;
    }

    Node< T >* head() {
        return m_head;
    }

    Node< T >* tail() {
        return m_tail;
    }

    void push_back( const T& v ) {
        auto* node = new Node< T >{ v, nullptr };
        if ( m_head == nullptr ) {
            m_head = m_tail = node;
            m_tail->next    = m_head;
        }
        else {
            m_tail->next = node;
            m_tail       = node;
            m_tail->next = m_head;
        }
    }

    T& pop_back() {
        if ( m_head == 0 ) {
            throw std::out_of_range( "circular list is empty" );
        }
        if ( m_head == m_tail ) {
            delete m_head;
            m_head = m_tail = nullptr;
        }
        else {
            Node< T >* p = m_head;
            while ( p->next != m_tail ) {
                p = p->next;
            }
            delete m_tail;
            m_tail       = p;
            m_tail->next = m_head;
        }
    }

    void insert_after( Node< T >* pos, const T& v ) {
        if ( pos == nullptr ) {
            throw std::invalid_argument( "pos is nullptr" );
        }
        auto* node   = new Node< T >{ v, nullptr };
        Node< T >* p = m_head;
        for ( ; p != pos; p = p->next ) {
            if ( p == m_head ) {
                throw std::invalid_argument( "pos is not in the list" );
            }
        }
        node->next = p->next;
        p->next    = node;
        if ( m_tail == m_head ) {
            m_tail = node;
        }
    }

    void erase_at( Node< T >* pos ) {
        if ( pos == nullptr ) {
            throw std::invalid_argument( "pos is nullptr" );
        }
        if ( m_tail == m_head ) {
            if ( pos == m_tail ) {
                delete m_head;
                m_head = m_tail = nullptr;
                return;
            }
            else {
                throw std::invalid_argument( "pos is not in the list" );
            }
        }
        if ( pos == m_head ) {
            Node< T >* p = m_head;
            m_head       = m_head->next;
            m_tail->next = m_head;
            delete p;
            return;
        }
        Node< T >* p = m_head->next;
        for ( ; p->next != pos; p = p->next ) {
            if ( p == m_head ) {
                throw std::invalid_argument( "pos is not in the list" );
            }
        }
        Node< T >* q = p->next;
        p->next      = q->next;
        delete q;
        if ( q == m_tail ) {
            m_tail = p;
        }
        pos = nullptr;
    }

    void print() {
        Node< T >* p = m_head;
        while ( p != m_tail ) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << p->data << endl;
    }
};
