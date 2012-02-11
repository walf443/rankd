#include "rankd.hpp"

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

