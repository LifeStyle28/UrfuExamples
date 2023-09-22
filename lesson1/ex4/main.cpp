#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

static int counter = 0;
static std::mutex mutex;

void foo_without_lock()
{
    for (auto i = 0; i < 100'000; ++i)
    {
        ++counter;
    }
}

void foo_with_lock()
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
    {
        const auto start = std::chrono::steady_clock::now();

        std::thread thread1(foo_without_lock);
        std::thread thread2(foo_without_lock);

        thread1.join();
        thread2.join();

        const auto end = std::chrono::steady_clock::now();

        const auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        std::cout << counter << " : " << ms << std::endl;
    }

    counter = 0;

    {
        const auto start = std::chrono::steady_clock::now();

        std::thread thread1(foo_with_lock);
        std::thread thread2(foo_with_lock);

        thread1.join();
        thread2.join();

        const auto end = std::chrono::steady_clock::now();

        const auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        std::cout << counter << " : " << ms << std::endl;
    }

    return EXIT_SUCCESS;
}
