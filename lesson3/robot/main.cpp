#include "robot.h"

namespace net = boost::asio;
namespace sys = boost::system;
using namespace std::literals;

void run_robots(net::io_context& io)
{
    auto r1 = std::make_shared<robot::Robot>(io, 1);
    auto r2 = std::make_shared<robot::Robot>(io, 2);

    // Робот r1 сперва поворачивается на 60 градусов, а потом идёт 4 метра
    r1->Rotate(60, [r1] {
        r1->Walk(4, [r1] {});
    });
    // Робот r2 сперва идёт 2 метра, а потом ещё 3 метра
    r2->Walk(2, [r2] {
        r2->Walk(3, [r2] {});
    });
}

int main()
{
    net::io_context io;

    run_robots(io);

    for (;;)
    {
        try
        {
            io.run();
            break;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    std::cout << "Done\n"sv;
}
