#include <iostream>

void foo(int a, int b)
{
    int c = 1;
    int d = 1;

    std::cout << "a = " << &a << std::endl;
    std::cout << "b = " << &b << std::endl;
    std::cout << "c = " << &c << std::endl;
    std::cout << "d = " << &d << std::endl;
}

int main()
{
    foo(1, 2);
    std::cout << "done" << std::endl;

    return EXIT_SUCCESS;
}
