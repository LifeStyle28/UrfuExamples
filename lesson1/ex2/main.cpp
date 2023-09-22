#include <iostream>
#include <thread>

static int counter = 0;

void foo()
{
    for (auto i = 0; i < 100'000; ++i)
    {
        ++counter;
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[])
{
    std::thread thread1(foo);
    std::thread thread2(foo);

    thread1.join();
    thread2.join();

    std::cout << counter << std::endl;

    return EXIT_SUCCESS;
}
