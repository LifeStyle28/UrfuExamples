#include <iostream>

#include "shared.h"

int main()
{
    while (true)
    {
        int N;
        std::cin >> N;

        switch (N)
        {
            case 1: inc_static_var(); break;
            case 2: print_var(); break;
            default: return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
