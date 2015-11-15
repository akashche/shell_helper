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
 * File:   StartProcessTask_test.cpp
 * Author: alex
 *
 * Created on November 14, 2015, 8:48 PM
 */

#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"
#include "staticlib/utils.hpp"
#include "staticlib/io.hpp"
#include "staticlib/reflection.hpp"
#include "staticlib/serialization.hpp"

#include "StartProcessTask.hpp"

namespace su = staticlib::utils;
namespace io = staticlib::io;
namespace sr = staticlib::reflection;
namespace ss = staticlib::serialization;
namespace sh = shellhelper;

#ifdef STATICLIB_WINDOWS
const std::string EXECUTABLE = "bin/CurrentDateTask_test.exe";
#else // STATICLIB_WINDOWS
const std::string EXECUTABLE = "bin/CurrentDateTask_test";
#endif // STATICLIB_WINDOWS
const std::string DESC_FILE = "StartProcessTask_test_desc.json";
const std::string OUT_FILE = "StartProcessTask_test_out.txt";

void test_start_process() {
    // write desc file
    auto sink = io::make_unbuffered_ostreambuf(
            su::FileDescriptor{DESC_FILE, 'w'});
    sr::ReflectedValue desc{
        {"executable", EXECUTABLE},
        {"out_file", OUT_FILE}};
    ss::dump_json(desc, sink);
    // start process
    sh::StartProcessTask sp{};
    auto pid = sp.start_process(DESC_FILE);
    slassert(pid > 0);
}

int main() {
    try {
        test_start_process();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

