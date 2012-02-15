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

int bench_get_rank_best(int argc, char **argv)
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
    unsigned long n = 1;
    while ( n < num ) {
        n *= 2;
    }
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(n/2);
    }
    struct timeval after_timeval;
    gettimeofday(&after_timeval, NULL);
    unsigned long runtime = ( after_timeval.tv_sec * 1000 + after_timeval.tv_usec / 1000 ) - ( before_timeval.tv_sec * 1000 + before_timeval.tv_usec / 1000 );
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete manager;

    return 0;
};


int bench_get_rank_worst(int argc, char **argv)
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
    unsigned long n = 1;
    while ( n < num ) {
        n *= 2;
    }
    std::cout << n << std::endl;
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(n/2-1);
    }
    struct timeval after_timeval;
    gettimeofday(&after_timeval, NULL);
    unsigned long runtime = ( after_timeval.tv_sec * 1000 + after_timeval.tv_usec / 1000 ) - ( before_timeval.tv_sec * 1000 + before_timeval.tv_usec / 1000 );
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete manager;

    return 0;
};

typedef struct {
        const char *name;
            int (*func)(int argc, char** argv);
} ACTION_TABLE;

int do_help_commands(int argc, char** argv);

static const ACTION_TABLE ACTIONS[] = {
    { "get_rank", bench_get_rank },
    { "get_rank_best", bench_get_rank_best },
    { "get_rank_worst", bench_get_rank_worst },
    { "help", do_help_commands },
};

void help_commands(char* program_name)
{
    std::cout << "USAGE: " << program_name << " [commands] [arg1, arg2, ...]" << std::endl;
    std::cout << std::endl;
    for (unsigned long i = 0; i < (sizeof(ACTIONS)/sizeof(ACTIONS[0])); i++ ) {
        std::cout << ACTIONS[i].name << std::endl;
    }
}

int do_help_commands(int argc, char** argv)
{
    help_commands(argv[0]);
    return 0;
}

int dispatch (char* subcmd, int argc, char **argv)
{
    for (unsigned long i = 0; i < (sizeof(ACTIONS)/sizeof(ACTIONS[0])); i++ ) {
        if ( strcmp(subcmd, ACTIONS[i].name) == 0 ) {
            return (* ACTIONS[i].func)(argc, argv);
        }
    }
    help_commands(argv[0]);
    return 1;
}

int main (int argc, char **argv)
{

    if ( argc <= 1 ) {
        help_commands(argv[0]);
        return 1;
    }
    return dispatch(argv[1], argc, argv);
}

