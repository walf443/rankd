#include "rankd.hpp"
#include "nanotap.h"

using namespace rankd;
int main(int argc, char**argv)
{
    Manager* manager = new Manager;
    ok(manager->top(37) != NULL, "top ok");
    is((unsigned long)1, manager->get_rank(37), "get_rank ok");
    ok(manager->top(37) != NULL, "top ok");

    done_testing();
}
