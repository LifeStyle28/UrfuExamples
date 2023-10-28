#include <iostream>

static int n = 0;

int add()
{
    if (n == 100)
    {
        return n;
    }

    std::cout << n << std::endl;
    ++n;
    return add();
}

int main()
{
    int a = add();

    return EXIT_SUCCESS;
}
