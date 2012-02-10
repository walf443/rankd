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
            this->item_map[item_id] = node;
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

    // TODO: どこのデータからupdateされたのか、を考慮してより効率よく更新する
    void Manager::update_rank_map(Node* node)
    {
        Node* nd = this->first;
        unsigned long rank = 1;
        unsigned long n = 1;

        while ( n <= this->num_of_items ) {
            std::map<unsigned long, Node*>::iterator iter = this->rank_map.find(n);
            if ( iter != this->rank_map.end() ) {
                // topから呼ばれているのを想定している
                //
                // データをひとつズラす
                Node* nd = (Node *)iter->second->prev;
                this->rank_map[n] = nd;
            } else {
                // rank_mapにデータがない場合なので、基本的にはそれ以上上位のランキングは存在するはずなので、
                // 最も近いデータから順番にたどる
                do {
                    if ( n == rank ) {
                        break;
                    }

                    rank++;
                } while ( nd = nd->next );
                this->rank_map[n] = nd;
            }
            n *= 2;
        }

    }

    unsigned long Manager::get_rank(unsigned long item_id)
    {
        std::map<Node*, unsigned long> reverse_rank_map;
        std::map<unsigned long, Node*>::iterator iter = this->rank_map.begin();
        while ( iter != this->rank_map.end() ) {
            reverse_rank_map[iter->second] = iter->first;

            iter++;
        }

        Node* node;
        std::map<unsigned long, Node*>::iterator item_iter = this->item_map.find(item_id);

        if ( item_iter == this->item_map.end() ) {
            return 0;
        }
        node = item_iter->second;

        if ( node == this->first ) {
            return 1;
        }

        unsigned long counter = 0;
        do {
            std::map<Node*, unsigned long>::iterator rank_iter = reverse_rank_map.find(node);
            if ( rank_iter != reverse_rank_map.end() ) {
                return rank_iter->second + counter;
            }

            counter++;
        } while ( node = node->prev );
        return 1;

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

#define NUM 10000

int main (int argc, char **argv)
{
    rankd::Manager* manager = new rankd::Manager();
    for (int i = 0; i < NUM; i++ ) {
        manager->top(i);
    }
    for (int i = 0; i < 10000; i++ ) {
        std::cout << i << ": " << manager->get_rank(i) << std::endl;
    }

    delete manager;

    return 0;
}

