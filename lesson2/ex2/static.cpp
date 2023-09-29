#include "static.h"

#include <iostream>

static int counter = 0;

void inc_static_var()
{
    ++counter;
}

void print_var()
{
    std::cout << "++++++++++" << std::endl;
    std::cout << counter << std::endl;
    std::cout << &counter << std::endl;
    std::cout << (void*)&inc_static_var << std::endl;
    std::cout << "++++++++++" << std::endl;
}
