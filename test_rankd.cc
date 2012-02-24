#include "rankd.hpp"
#include "nanotap.h"

using namespace rankd;

void top_same_value()
{
    diag("Testing: top_same_value");
    Manager* manager = new Manager;
    ok(manager->top(37) != NULL, "top ok");
    is((unsigned long)1, manager->get_rank(37), "get_rank ok");
    ok(manager->top(37) != NULL, "top ok");

    delete manager;
}

void top_test2()
{
    diag("Testing: top_test2");
    Manager* manager = new Manager;
    ok(manager->top(82) != NULL, "top ok");
    is(manager->get_rank(82), (unsigned long)1, "82 should be rank 1");
    is(manager->get_node_by_rank(1)->value, (unsigned long)82, "rank 1 should be 82");

    ok(manager->top(1)  != NULL, "top ok");
    is(manager->get_rank(1), (unsigned long)1, "1 should be rank 1");
    is(manager->get_rank(82), (unsigned long)2, "82 should be rank 2");
    is(manager->get_node_by_rank(1)->value, (unsigned long)1, "rank 1 should be 1");
    is(manager->get_node_by_rank(2)->value, (unsigned long)82, "rank 2 should be 82");

    ok(manager->top(82) != NULL, "top ok");
    is(manager->get_rank(82), (unsigned long)1, "82 should be rank 1");
    is(manager->get_rank(1), (unsigned long)2, "1 should be rank 2");
    is(manager->get_node_by_rank(1)->value, (unsigned long)82, "rank 1 should be 82");
    is(manager->get_node_by_rank(2)->value, (unsigned long)1, "rank 2 should be 1");

    ok(manager->top(2)  != NULL, "top ok");
    is(manager->get_rank(2), (unsigned long)1, "2 should be rank 1");
    is(manager->get_rank(82), (unsigned long)2, "82 should be rank 2");
    is(manager->get_rank(1), (unsigned long)3, "1 should be rank 3");
    is(manager->get_node_by_rank(1)->value, (unsigned long)2, "rank 1 should be 2");
    is(manager->get_node_by_rank(2)->value, (unsigned long)82, "rank 2 should be 82");
    is(manager->get_node_by_rank(3)->value, (unsigned long)1, "rank 3 should be 1");

    ok(manager->top(3)  != NULL, "top ok");
    is(manager->get_rank(3), (unsigned long)1, "3 should be rank 1");
    is(manager->get_rank(2), (unsigned long)2, "2 should be rank 2");
    is(manager->get_rank(82), (unsigned long)3, "82 should be rank 3");
    is(manager->get_rank(1), (unsigned long)4, "1 should be rank 4");
    is(manager->get_node_by_rank(1)->value, (unsigned long)3, "rank 1 should be 3");
    is(manager->get_node_by_rank(2)->value, (unsigned long)2, "rank 2 should be 2");
    is(manager->get_node_by_rank(3)->value, (unsigned long)82, "rank 3 should be 82");
    is(manager->get_node_by_rank(4)->value, (unsigned long)1, "rank 4 should be 1");

    ok(manager->top(4)  != NULL, "top ok");

    delete manager;
}

int main(int argc, char**argv)
{
    top_same_value();
    top_test2();
    done_testing();
}
