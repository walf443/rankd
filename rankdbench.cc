#include "rankd.hpp"

#include <iostream>
#include <sys/time.h>

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
    struct timeval before_timeval;
    gettimeofday(&before_timeval, NULL);
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(i);
    }
    struct timeval after_timeval;
    gettimeofday(&after_timeval, NULL);
    unsigned long runtime = ( after_timeval.tv_sec * 1000 + after_timeval.tv_usec / 1000 ) - ( before_timeval.tv_sec * 1000 + before_timeval.tv_usec / 1000 );
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete manager;

    return 0;
}

void help_commands(void)
{
}

int do_help_commands(int argc, char** argv)
{
    help_commands();
    return 0;
}

typedef struct {
        const char *name;
            int (*func)(int argc, char** argv);
} ACTION_TABLE;

static const ACTION_TABLE ACTIONS[] = {
    { "get_rank", bench_get_rank },
    { "help", do_help_commands },
};

int dispatch (char* subcmd, int argc, char **argv)
{
    for (unsigned long i = 0; i < (sizeof(ACTIONS)/sizeof(ACTIONS[0])); i++ ) {
        if ( strcmp(subcmd, ACTIONS[i].name) == 0 ) {
            return (* ACTIONS[i].func)(argc, argv);
        }
    }
    help_commands();
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

