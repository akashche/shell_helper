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
 * File:   CurrentDateTask.cpp
 * Author: alex
 * 
 * Created on November 12, 2015, 1:15 PM
 */

#include <string>
#include <mutex>
#include <chrono>
#include <array>
#include <ctime>

#include "staticlib/utils.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "CurrentDateTask.hpp"

namespace shellhelper {

class CurrentDateTask::Impl : public staticlib::pimpl::PimplObject::Impl {
    std::mutex mutex;
    
public:
    Impl() { }
    
    std::string current_date(CurrentDateTask&, const std::string& format) {
        auto time = local_time_sync();
        std::array<char, 256> buf;
        auto len = std::strftime(buf.data(), buf.size(), format.c_str(), std::addressof(time));
        if (0 == len) throw ShellHelperException(TRACEMSG(std::string{} + 
                "Error formating date using format string: [" + format + "]"));
        return std::string(buf.data(), len);
    }
    
private:
    std::tm local_time_sync() {
        std::lock_guard<std::mutex> guard{mutex};
        std::time_t t = std::time(nullptr);
        return *std::localtime(&t);
    }

};
PIMPL_FORWARD_CONSTRUCTOR(CurrentDateTask, (), (), ShellHelperException)
PIMPL_FORWARD_METHOD(CurrentDateTask, std::string, current_date, (const std::string&), (), ShellHelperException)

} // namespace
