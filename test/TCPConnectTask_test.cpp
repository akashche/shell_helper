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
    //    (void) success;
    //    assert(success.empty());

    std::string fail = tct.check_connection("127.0.0.1", 1234);
    slassert(!fail.empty());
}

int main() {
    try {
        test_connect();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

