#include "rankd.hpp"

namespace rankd {
    Manager::Manager()
    {
        this->last = new Node();
        this->first = this->last;
    }

    Manager::~Manager()
    {
        delete this->last;
    }

    Node* Manager::top(unsigned long item_id)
    {
        Node * node = new Node();
        node->value = item_id;
        node->next = this->first;
        this->first = node;
        return node;
    }

    unsigned long get_rank(unsigned long item_id)
    {
    }

    Node* get_node_by_rank(unsigned long rank)
    {
    }
}

int main (int argc, char **argv)
{
    rankd::Manager* manager = new rankd::Manager();
    for (int i = 0; i < 10000000; i++ ) {
        manager->top(i);
    }

    return 0;
}
