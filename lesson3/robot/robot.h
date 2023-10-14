#pragma once

#ifdef WIN32
#include <sdkddkver.h>
#endif

#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <memory>

namespace robot
{

namespace net = boost::asio;
namespace chrono = std::chrono;
using namespace std::literals;
using boost::system::error_code;

class Robot
{
public:
    using Duration = net::steady_timer::duration;

    constexpr static double SPEED = 2;  // скорость в м/с
    constexpr static double ROTATION_SPEED = 30;  // скорость поворота (градусов в секунду)

    Robot(net::io_context& io, int id) :
        m_timer{std::make_shared<net::steady_timer>(io)},
        m_id{id}
    {
    }

    // cb - функция обратного вызова.
    // Она будет вызвана асинхронно после того, как робот пройдёт заданную дистанцию
    template <typename Callback>
    void Walk(const int distance, Callback&& cb)
    {
        const auto t = 1s * distance / SPEED;
        std::cout << m_id << "> Walk for "sv << t.count() << "s\n"sv;

        m_timer->expires_after(chrono::duration_cast<Duration>(t));

        m_timer->async_wait([distance, cb = std::forward<Callback>(cb), this, timer = m_timer](error_code ec) {
            if (ec)
            {
                throw std::runtime_error(ec.what());
            }
            m_distance += distance;
            std::cout << m_id << "> Walked distance: "sv << m_distance << "m\n"sv;
            cb();
        });
    }

    // cb - будет вызвана асинхронно после того, как робот повернётся на нужный угол
    template <typename Callback>
    void Rotate(const int angle, Callback&& cb)
    {
        const auto t = 1s * std::abs(angle) / ROTATION_SPEED;
        std::cout << m_id << "> Start rotating by "sv << angle << "deg.\n"sv;

        m_timer->expires_after(chrono::duration_cast<Duration>(t));

        m_timer->async_wait([angle, cb = std::forward<Callback>(cb), this, t, timer = m_timer](error_code ec) {
            if (ec)
            {
                throw std::runtime_error(ec.what());
            }
            m_angle = (m_angle + angle) % 360;
            std::cout << m_id << "> Rotation angle: "sv << m_angle << "deg. for "sv << t.count() << "s\n"sv;
            cb();
        });

    }

private:
    std::shared_ptr<net::steady_timer> m_timer;
    int m_id;
    int m_angle = 0;
    int m_distance = 0;
};

} // namespace robot
