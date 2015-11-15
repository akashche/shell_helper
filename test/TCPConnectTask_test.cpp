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
 * File:   TCPConnectTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 9:01 PM
 */

#include <string>
#include <iostream>
#include <cstdint>

#include "staticlib/utils/assert.hpp"

#include "TCPConnectTask.hpp"

namespace sh = shellhelper;

void test_connect() {
    sh::TCPConnectTask tct{};

//    std::string success = tct.check_connection("127.0.0.1", 22);
//    slassert(success.empty());

    std::string fail = tct.check_connection("127.0.0.1", 1234);
    slassert(!fail.empty());
}

void test_connect_wait() {
    sh::TCPConnectTask tct{};
    bool res = tct.wait_for_connection("127.0.0.1", 1234, std::chrono::seconds{2});
    slassert(!res);
}

int main() {
    try {
        test_connect();
        test_connect_wait();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

