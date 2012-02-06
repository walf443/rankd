#include "rankd.hpp"
#include <iostream>

namespace rankd {
    Manager::Manager()
    {
        this->last = new Node();
        this->first = this->last;
    }

    Manager::~Manager()
    {
        Node* node = this->first;

        do {
            delete node;
        } while ( node = node->next );
    }

    Node* Manager::top(unsigned long item_id)
    {
        std::map<long unsigned, Node*>::iterator iter = this->item_map.find(item_id);
        if ( iter == this->item_map.end() ) {
            Node* node = new Node();
            this->num_of_items++;
            node->value = item_id;
            node->next = this->first;
            this->first->prev = node;
            this->first = node;
            this->item_map.insert( std::make_pair(item_id, node) );
            this->update_rank_map(node);
            return node;
        } else {
            Node *node, *prev, *next;
            node = iter->second;
            prev = node->prev;
            next = node->next;
            
            prev->next = next;
            next->prev = prev;

            node->prev = NULL;
            node->next = this->first;
            this->first->prev = node;
            this->update_rank_map(node);

            return node;
        }
    }

    void Manager::update_rank_map(Node* node)
    {
        Node* nd = this->first;
        unsigned long rank = 1;
        unsigned long n = 1;
        while ( n < this->num_of_items ) {
            std::map<unsigned long, Node*>::iterator iter = this->rank_map.find(n);
            if ( iter == this->rank_map.end() ) {
                do {
                    if ( n == rank ) {
                        break;
                    }

                    rank++;
                } while ( nd = nd->next );
                this->rank_map.insert(std::make_pair(n, nd));
            } else {
                // topから呼ばれているのを想定している
                //
                // データをひとつズラす
                this->rank_map.insert(std::make_pair(n, iter->second->prev));
            }
            n *= 2;
        }
    }

    unsigned long Manager::get_rank(unsigned long item_id)
    {
        unsigned long rank = 1;
        Node* node = this->first;
        do {
            if ( node->value == item_id ) {
                return rank;
            }

            rank++;
        } while ( node = node->next );
        return 0;
    }

    Node* Manager::get_node_by_rank(unsigned long rank)
    {
        unsigned long counter = 1;
        Node* node = this->first;
        do {
            if ( counter == rank ) {
                return node;
            }
            counter++;
        } while ( node = node->next );
    }
}

#include <iostream>

int main (int argc, char **argv)
{
    rankd::Manager* manager = new rankd::Manager();
    for (int i = 0; i < 10000000; i++ ) {
        manager->top(i);
    }
    for (int i = 0; i < 100; i++ ) {
        std::cout << i << ": " << manager->get_rank(i) << std::endl;
    }
    delete manager;

    return 0;
}

