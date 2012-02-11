#include "rankd.hpp"

#include <iostream>
using namespace rankd;

int bench_get_rank (unsigned long num)
{
    std::cout << "num: " << num << std::endl;
    return 0;
}

int dispatch (char* subcmd, int argc, char **argv)
{
    std::cout << subcmd << std::endl;

    if ( strcmp(subcmd, "get_rank") == 0 ) {
        return bench_get_rank(atol(argv[2]));
    }

    return 0;
}

int main (int argc, char **argv)
{

    if ( argc <= 1 ) {
        std::cout << "Usage: " << argv[0] << " subcommand [args, ....]" << std::endl;
        exit(1);
    }
    return dispatch(argv[1], argc, argv);

    return 0;
}

