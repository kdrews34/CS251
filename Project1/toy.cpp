#include "TravelOptions.h"

#include <stdlib.h>
#include <iostream>

// using namespace std;

/*
 simple demo program exercising some of the TravelOptions functions.

to compile:  g++ -std=c++11 toy.cpp

 purpose:  just to make sure you have an idea of how to write 
             driver/tester programs (this is not itself a tester program
             per-se, just a pretty random sequence of calls..
*/

int main(int argc, char *argv[])
{
    TravelOptions *options_p, *options_p2, *options_p3;

    std::vector<std::pair<double, double>> // change this to test vvvvvvvvvvvvvv
        vec{ {1, 9}, {2, 8}, {3, 7}, {4, 6}, {5, 5},{6, 4}, {7, 3}, {8, 2}, {9, 1} };

    std::vector<std::pair<double, double>> 
        vec2{ };

    // remember:  from_vec is a static function (hence, TravelOptions:: form)
    options_p = TravelOptions::from_vec(vec);
    options_p2 = TravelOptions::from_vec(vec2);

    printf("options_p list:\n");
    options_p->display();

    // options_p3 = options_p->split_sorted_pareto(9);

    // printf("under-budget options:\n");
    // options_p->display();
    // printf("over-budget options:\n");
    // options_p3->display();
    // printf("options_p2 list\n");
    // options_p2->display();
    // std::cout << "size: " << options_p->size() << std::endl;

    // TravelOptions::Relationship r;
    // r = TravelOptions::compare(8.0, 3.0, 9.0, 1.9); // change this to test***************
    // if (r == TravelOptions::incomparable)
    //     std::cout << "INCOMPARABLE!" << std::endl;

    // vec2 = options_p->to_vec();

    // std::cout << "CONTENTS OF EXPORTED VECTOR:\n";
    // for (int i = 0; i < vec2->size(); i++)
    // {
    //     std::cout << (*vec2)[i].first << (*vec2)[i].second << std::endl;
    // }

    // std::cout << "\n";

    if (options_p->is_sorted())
        std::cout << "p is sorted." << std::endl;
    else
        std::cout << "p is NOT sorted." << std::endl;

    if (options_p->is_pareto())
        std::cout << "p is pareto!" << std::endl;
    else
        std::cout << "p is NOT pareto." << std::endl;

    if (options_p->is_pareto_sorted())
        std::cout << "p is pareto/sorted." << std::endl;
    else
        std::cout << "p is NOT pareto/sorted." << std::endl;

    if (options_p->insert_sorted(10, 1.5)) //change this to test******************
    {
        printf("insert_sorted() worked\n");
    }

    if (options_p->insert_pareto_sorted(4, 5)) //change this to test******************
        std::cout << "INSERT_PARETO_SORTED WORKED!" << std::endl;

    //options_p3 = options_p->union_pareto_sorted(*options_p2);
    // options_p3 = options_p->join_plus_max(*options_p2);

    // printf("options_p3 (max thing of p and p2):\n");
    // options_p3->display();

    // if (options_p->prune_sorted())
    //     std::cout << "prune_sorted worked!" << std::endl;

    // options_p->display();

    // delete options_p3;

    // options_p3 = options_p->join_plus_plus(*options_p2);

    // delete options_p3;
    // options_p3 = options_p->join_plus_max(*options_p2);

    options_p->clear();
    delete options_p;
    delete options_p2;
    //delete options_p3;

    return 0;
}