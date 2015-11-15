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
 * File:   ReplacerTask_test.cpp
 * Author: alex
 *
 * Created on November 13, 2015, 10:19 PM
 */

#include <string>
#include <array>
#include <iostream>

#include "staticlib/utils/assert.hpp"
#include "staticlib/utils.hpp"
#include "staticlib/io.hpp"
#include "staticlib/reflection.hpp"
#include "staticlib/serialization.hpp"

#include "ReplacerTask.hpp"

namespace su = staticlib::utils;
namespace io = staticlib::io;
namespace sr = staticlib::reflection;
namespace ss = staticlib::serialization;
namespace sh = shellhelper;

const std::string SRC_FILE = "ReplacerTask_test_src.txt";
const std::string PARAMS_FILE = "ReplacerTask_test_params.txt";
const std::string DEST_FILE = "ReplacerTask_test_dest.txt";

void write_src_data() {
    su::FileDescriptor src{SRC_FILE, 'w'};
    std::string data{"41 {{foo}} 43 {{bar}}"};
    src.write(data.c_str(), data.length());
}

void write_params() {
    auto sink = io::make_unbuffered_ostreambuf(
            su::FileDescriptor{PARAMS_FILE, 'w'});
    sr::ReflectedValue params{
        {"foo", "42"},
        {"bar", "44"}};
    ss::dump_json(params, sink);
}

void test_replace() {
    write_src_data();
    write_params();
    sh::ReplacerTask task{};
    task.replace_files(SRC_FILE, PARAMS_FILE, DEST_FILE);
    su::FileDescriptor dest{DEST_FILE, 'r'};
    io::string_sink sink{};
    std::array<char, 8192> buf;
    io::copy_all(dest, sink, buf.data(), buf.size());
    slassert("41 42 43 44" == sink.get_string());
}

int main() {
    try {
        test_replace();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

