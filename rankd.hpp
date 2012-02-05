#ifndef RANKD_H

#include <map>

namespace rankd {
    class Node {
    public:
        Node* prev;
        Node* next;
        unsigned long value;
    };

    class Manager {
    public:
        Manager();
        ~Manager();
        Node* top(unsigned long item_id);
        unsigned long get_rank(unsigned long item_id);
        Node* get_node_by_rank(unsigned long rank);
    private:
        Node* first;
        Node* last;
        std::map<unsigned long, Node*> item_map;
    };
}

#define RANKD_H
#endif
