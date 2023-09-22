#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;
static std::mutex mutex;

void foo()
{
    for (auto i = 0; i < 100'000; ++i)
    {
        // Начало критической секции
        mutex.lock();
        ++counter;
        mutex.unlock();
        // Окончание критической секции
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
