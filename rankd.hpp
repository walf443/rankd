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
        unsigned long num_of_items;
        std::map<unsigned long, Node*> item_map;
        std::map<unsigned long, Node*> rank_map;
        void update_rank_map(Node* node);
    };
}

#define RANKD_H
#endif
