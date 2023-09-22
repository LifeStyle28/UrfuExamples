#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;
static std::mutex mutex1;
static std::mutex mutex2;

void foo1()
{
    for (auto i = 0; i < 100'000; ++i)
    {
        // Начало критической секции
        mutex1.lock();
        mutex2.lock();
        ++counter;
        mutex1.unlock();
        mutex2.unlock();
        // Окончание критической секции
    }
}

void foo2()
{
    for (auto i = 0; i < 100'000; ++i)
    {
        // Начало критической секции
        mutex2.lock();
        mutex1.lock();
        ++counter;
        mutex1.unlock();
        mutex2.unlock();
        // Окончание критической секции
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[])
{
    std::thread thread1(foo1);
    std::thread thread2(foo2);

    thread1.join();
    thread2.join();

    std::cout << counter << std::endl;

    return EXIT_SUCCESS;
}
