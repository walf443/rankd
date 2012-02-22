#include "rankd.hpp"

#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace rankd;

namespace rankd {
    class Timer {
    public:
        void start();
        void stop();
        unsigned long get_result();
    private:
        struct timeval start_timeval;
        struct timeval end_timeval;
    };

    void Timer::stop()
    {
        gettimeofday(&end_timeval, NULL);
    }
    void Timer::start()
    {
        gettimeofday(&start_timeval, NULL);
    }
    unsigned long Timer::get_result()
    {
        return ( end_timeval.tv_sec * 1000 + end_timeval.tv_usec / 1000 ) - ( start_timeval.tv_sec * 1000 + start_timeval.tv_usec / 1000 );
    }
}

rankd::Manager* prepare(unsigned long num)
{
    rankd::Manager *manager = new Manager();
    for (unsigned long i = num; i > 0; i-- ) {
        manager->top(i);
    }
    char buffer[BUFSIZ];
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    std::cout << "Memory Usage: " << ru.ru_maxrss << std::endl;
    return manager;
}

int bench_get_rank (int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(i);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
}

int bench_get_rank_top(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(1);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
};

int bench_get_rank_last(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(num);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
};

int bench_get_rank_not_found(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(num+1);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
};

int bench_get_rank_best(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    unsigned long n = 1;
    while ( n < num ) {
        n *= 2;
    }
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(n/2);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
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
    Manager* manager = prepare(num);

    Timer *timer = new Timer;
    timer->start();
    unsigned long n = 1;
    while ( n < num ) {
        n *= 2;
    }
    for (unsigned long i = 1; i <= num; i++ ) {
        manager->get_rank(n/2-1);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
};

int bench_top_no_dup(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);

    Manager* manager = new Manager();
    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = num; i > 0; i-- ) {
        manager->top(i);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
}



int bench_top_rand(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }

    unsigned long num = atol(argv[2]);

    srandomdev();
    Manager* manager = new Manager();
    Timer *timer = new Timer;
    timer->start();
    for (unsigned long i = num; i > 0; i-- ) {
        unsigned long item_id = random() % num;
        manager->top(item_id);
    }
    timer->stop();
    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
}

int bench_get_node_by_rank(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }
    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer* timer = new Timer();
    timer->start();
    for (unsigned long i = num; i > 0; i-- ) {
        manager->get_node_by_rank(i);
    }
    timer->stop();

    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete manager;

    return 0;
}

int bench_get_node_by_rank_best(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }
    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer* timer = new Timer();
    unsigned long n = 1;

    while ( n < num ) {
        n *= 2;
    }

    timer->start();
    for (unsigned long i = num; i > 0; i-- ) {
        manager->get_node_by_rank(n/2);
    }
    timer->stop();

    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
}

int bench_get_node_by_rank_worst(int argc, char **argv)
{
    if ( argc < 3 ) {
        std::cout << "USAGE: " << argv[0] << " " << argv[1] << " num" << std::endl;
        return 1;
    }
    unsigned long num = atol(argv[2]);
    Manager* manager = prepare(num);

    Timer* timer = new Timer();
    unsigned long n = 1;

    while ( n < num ) {
        n *= 2;
    }

    timer->start();
    for (unsigned long i = num; i > 0; i-- ) {
        manager->get_node_by_rank((n/4)+1);
    }
    timer->stop();

    unsigned long runtime = timer->get_result();
    std::cout << "num:\t\t" << num << std::endl;
    std::cout << "finished:\t" << runtime << "ms" << std::endl;
    std::cout << "average:\t" << 1.0 * runtime / num << "ms" << std::endl;

    delete timer;
    delete manager;

    return 0;
}
typedef struct {
        const char *name;
        int (*func)(int argc, char** argv);
} ACTION_TABLE;

int do_help_commands(int argc, char** argv);

static const ACTION_TABLE ACTIONS[] = {
    { "get_rank", bench_get_rank },
    { "get_rank_best", bench_get_rank_best },
    { "get_rank_worst", bench_get_rank_worst },
    { "get_rank_top", bench_get_rank_top },
    { "get_rank_last", bench_get_rank_last },
    { "get_rank_not_found", bench_get_rank_not_found },
    { "top_no_dup", bench_top_no_dup },
    { "top_rand", bench_top_rand },
    { "get_node_by_rank", bench_get_node_by_rank },
    { "get_node_by_rank_best", bench_get_node_by_rank_best },
    { "get_node_by_rank_worst", bench_get_node_by_rank_worst },
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

