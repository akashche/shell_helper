/* 
 * File:   TCPConnectTask.hpp
 * Author: alex
 *
 * Created on November 12, 2015, 1:19 PM
 */

#ifndef SHELL_HELPER_TCPCONNECTTASK_HPP
#define	SHELL_HELPER_TCPCONNECTTASK_HPP

#include <string>
#include <chrono>
#include <cstdint>

#include "staticlib/pimpl.hpp"

namespace shellhelper {

class TCPConnectTask : public staticlib::pimpl::PimplObject {
protected:
    class Impl;

public:
    PIMPL_CONSTRUCTOR(TCPConnectTask)

    TCPConnectTask();

    std::string check_connection(const std::string& ip, uint16_t port);
    
    bool wait_for_connection(const std::string& ip, uint16_t port, std::chrono::seconds timeout);
};

} // namespace

#endif	/* SHELL_HELPER_TCPCONNECTTASK_HPP */

