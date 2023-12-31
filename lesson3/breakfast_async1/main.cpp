#ifdef WIN32
#include <sdkddkver.h>
#endif

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

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
        net::steady_timer t(ioc, 5s);
        std::cout << "Make coffee"sv << std::endl;
        t.async_wait([](sys::error_code ec) {
            if (ec)
            {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Pour coffee in the cup"sv << std::endl;
        });
    }
    // Жарим яичницу 3 секунды
    {
        net::steady_timer t(ioc, 3s);
        std::cout << "Fry eggs"sv << std::endl;
        t.async_wait([](sys::error_code ec) {
            if (ec)
            {
                throw std::runtime_error("Wait error: "s + ec.message());
            }
            std::cout << "Put eggs onto the plate"sv << std::endl;
        });
    }

    std::cout << "Run asynchronous operations"sv << std::endl;
    ioc.run();

    const auto cook_duration = duration<double>(steady_clock::now() - start_time);
    std::cout << "Breakfast has been cooked in "sv << cook_duration.count() << "s"sv << std::endl;
}
