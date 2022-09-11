#include <iostream>

#include "weighted_graph.hpp"

void test_basic()
{
    std::cout << "============TEST BASIC============\n";
    Weighted_graph g ({"a", "b", "c", "d"},
            {{"a", "b", 1}, {"b", "c", 2}});

    g.print();

    g.print_path("a", "b");
    g.print_path("b", "c");
    g.print_path("a", "c");
    g.print_path("a", "d");
}

void test_modifications()
{
    std::cout << "============TEST DYNAMIC============\n";
    Weighted_graph g ({"a", "b", "c", "d"},
                      {{"a", "b", 1}, {"b", "c", 2}});

    std::cout << "---------DELETE NODE-----\n";
    g.delete_node("a");
    g.print();

    std::cout << "--------ADD EDGE---------\n";

    g.add_edge("d", "b", 3);
    g.print();

    std::cout << "------CHANGE WEIGHT------\n";

    g.change_weight("d", "b", 10);
    g.print();

    std::cout << "-------DELETE EDGE-------\n";

    g.delete_edge("b", "d");
    g.print();
}

void test_path()
{
    std::cout << "============TEST PATH============\n";
    Weighted_graph g ({"a", "b", "c", "d", "e", "f"},
                      {{"a", "b", 1}, {"b", "c", 2}, {"b", "d", 2}, {"e", "f", 4}});

    g.print_path("a", "a");
    g.print_path("a", "d");
    g.print_path("d", "f");
}

int main()
{
    test_basic();
    test_modifications();
    test_path();

    return 0;
}
