#ifndef RANKD_H

namespace rankd {
    class Node {
    public:
    protected:
        Node* prev;
        Node* next;
    private:
    };

    class Manager {
    public:
        Manager();
        ~Manager();
        Node* top(unsigned long item_id);
        Node* get_rank(unsigned long item_id);
        Node* get_node_by_rank(unsigned long rank);
    private:
        Node* first;
        Node* last;
    };
}

#define RANKD_H
#endif
