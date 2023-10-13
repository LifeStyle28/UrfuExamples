#ifdef WIN32
#include <sdkddkver.h>
#endif

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <memory>

namespace net = boost::asio;
namespace sys = boost::system;
using namespace std::chrono;
using namespace std::literals;

int main()
{
    // заводим контекст ввода-вывода
    net::io_context ioc;

    const auto start_time = steady_clock::now();

    // Варим кофе 5 секунд
    {
        auto t = std::make_shared<net::steady_timer>(ioc, 5s);
        std::cout << "Make coffee"sv << std::endl;
        t->async_wait([t](sys::error_code ec) {
            if (ec)
            {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Pour coffee in the cup. Thread id: "sv << std::this_thread::get_id() << std::endl;
        });
    }
    // Жарим яичницу 3 секунды
    {
        auto t = std::make_shared<net::steady_timer>(ioc, 3s);
        std::cout << "Fry eggs"sv << std::endl;
        t->async_wait([t](sys::error_code ec) {
            if (ec)
            {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Put eggs onto the plate. Thread id: "sv << std::this_thread::get_id() << std::endl;
        });
    }

    try
    {
        std::cout << "Run asynchronous operations"sv << std::endl;
        ioc.run();

        const auto cook_duration = duration<double>(steady_clock::now() - start_time);
        std::cout << "Breakfast has been cooked in "sv << cook_duration.count() << "s"sv << std::endl;
        std::cout << "Thread id: "sv << std::this_thread::get_id() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
