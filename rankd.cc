#include "rankd.hpp"

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
        Node* node = new Node();
        node->value = item_id;
        node->next = this->first;
        this->first = node;
        return node;
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
    }

    Node* Manager::get_node_by_rank(unsigned long rank)
    {
    }
}

int main (int argc, char **argv)
{
    rankd::Manager* manager = new rankd::Manager();
    for (int i = 0; i < 10000000; i++ ) {
        manager->top(i);
    }
    for (int i = 0; i < 100; i++ ) {
        manager->get_rank(i);
    }
    delete manager;

    return 0;
}
