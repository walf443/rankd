#include "rankd.hpp"

#include <iostream>
using namespace rankd;

int bench_get_rank (int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = new Manager();

    for (unsigned long i = 1; i <= num; i++ ) {
        manager->top(i);
    }
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(i);
    }

    delete manager;

    return 0;
}

int dispatch (char* subcmd, int argc, char **argv)
{
    if ( strcmp(subcmd, "get_rank") == 0 ) {
        return bench_get_rank(argc, argv);
    }
    return 1;
}

int main (int argc, char **argv)
{

    if ( argc <= 1 ) {
        std::cout << "Usage: " << argv[0] << " subcommand [args, ....]" << std::endl;
        exit(1);
    }
    return dispatch(argv[1], argc, argv);
}

