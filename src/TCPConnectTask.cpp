/* 
 * File:   TCPConnectTask.cpp
 * Author: alex
 * 
 * Created on November 12, 2015, 1:19 PM
 */

#include <string>
#include <mutex>
#include <chrono>
#include <atomic>

#include "asio.hpp"

#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "TCPConnectTask.hpp"

namespace shellhelper {

class TCPConnectTask::Impl : public staticlib::pimpl::PimplObject::Impl {
    
public:

    Impl() { }
    
    bool check_connection(TCPConnectTask&, const std::string& ip, uint16_t port) {
        asio::io_service service{};
        asio::ip::tcp::socket socket{service, asio::ip::tcp::v4()};
        auto addr = asio::ip::address_v4::from_string(ip);
        asio::ip::tcp::endpoint ep{addr, port};
        asio::steady_timer timer{service};
        std::mutex mutex{};
        std::atomic_bool connect_cancelled{false};
        std::atomic_bool timer_cancelled{false};
        std::atomic_bool connect_success{false};
        timer.expires_from_now(std::chrono::seconds(1));
        socket.async_connect(ep, [&](const asio::error_code& ec) {
            std::lock_guard<std::mutex> guard{mutex};
            if (connect_cancelled) return;
            timer_cancelled = true;
            timer.cancel();
            connect_success = !ec;
        });        
        timer.async_wait([&](const asio::error_code&) {
            std::lock_guard<std::mutex> guard{mutex};
            if (timer_cancelled) return;
            connect_cancelled = true;
            socket.cancel();
        });
        service.run();
        return connect_success.load();
    }
    
};
PIMPL_FORWARD_CONSTRUCTOR(TCPConnectTask, (), (), ShellHelperException)
PIMPL_FORWARD_METHOD(TCPConnectTask, bool, check_connection, (const std::string&)(uint16_t), (), ShellHelperException)

} // namespace




