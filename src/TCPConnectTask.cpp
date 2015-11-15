/*
 * Copyright 2015, akashche at redhat.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
#include <thread>
#include <cstdint>

#include "asio.hpp"
#include "format.h"

#include "staticlib/utils.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "TCPConnectTask.hpp"

namespace shellhelper {

namespace { // anonymous
namespace su = staticlib::utils;
} // namespace

class TCPConnectTask::Impl : public staticlib::pimpl::PimplObject::Impl {
    
public:

    Impl() { }
    
    std::string check_connection(TCPConnectTask&, const std::string& ip, uint16_t port) {
        Checker checker{*this, ip, port, std::chrono::seconds(1)};
        return checker.check();
    }
    
    bool wait_for_connection(TCPConnectTask&, const std::string& ip, uint16_t port, std::chrono::seconds timeout) {
        Checker checker{*this, ip, port, std::chrono::seconds(1)};
        uint32_t start = current_time_in_seconds();
        while (current_time_in_seconds() - start < timeout.count()) {
            std::string err = checker.check();
            if (err.empty()) return true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return false;
    }
    
private:
    // http://stackoverflow.com/a/2834294/314015
    uint32_t current_time_in_seconds() {
        auto time = std::chrono::system_clock::now(); // get the current time
        auto since_epoch = time.time_since_epoch(); // get the duration since epoch
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
        return static_cast<uint32_t>(seconds.count()); // just like java (new Date()).getTime();
    }

    class Checker {
        TCPConnectTask::Impl& parent;
        asio::io_service service{};
        asio::ip::tcp::endpoint endpoint;
        std::chrono::seconds timeout;
        
    public:
        Checker(TCPConnectTask::Impl& parent, const std::string& ip, uint16_t port, 
                std::chrono::seconds timeout) :
        parent(parent),
        endpoint(asio::ip::address_v4::from_string(ip), port),
        timeout(timeout) { }
        
        std::string check() {
            service.reset();
            asio::ip::tcp::socket socket{service, asio::ip::tcp::v4()};
            asio::steady_timer timer{service};
            std::mutex mutex{};
            std::atomic_bool connect_cancelled{false};
            std::atomic_bool timer_cancelled{false};
            std::string error_message = "";
            timer.expires_from_now(std::chrono::seconds(1));
            socket.async_connect(endpoint, [&](const asio::error_code& ec) {
                std::lock_guard<std::mutex> guard{mutex};
                if (connect_cancelled) return;
                timer_cancelled = true;
                timer.cancel();
                if(ec) {
                    error_message = fmt::format("ERROR: {} ({})", ec.message(), su::to_string(ec.value()));
                }
            });
            timer.async_wait([&](const asio::error_code&) {
                std::lock_guard<std::mutex> guard{mutex};
                if (timer_cancelled) return;
                connect_cancelled = true;
                socket.close();
                error_message = "ERROR: Connection timed out (-1)";
            });
            service.run();
            return error_message;
        }               
    };
    
};
PIMPL_FORWARD_CONSTRUCTOR(TCPConnectTask, (), (), ShellHelperException)
PIMPL_FORWARD_METHOD(TCPConnectTask, std::string, check_connection, (const std::string&)(uint16_t), (), ShellHelperException)
PIMPL_FORWARD_METHOD(TCPConnectTask, bool, wait_for_connection, (const std::string&)(uint16_t)(std::chrono::seconds), (), ShellHelperException)

} // namespace




