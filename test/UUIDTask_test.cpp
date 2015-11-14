/* 
 * File:   UUIDTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 3:11 PM
 */

#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"

#include "UUIDTask.hpp"

namespace sh = shellhelper;

void test_uuid() {
    std::string uuid = sh::UUIDTask().generate_uuid();
    slassert(uuid.length() > 0);
}

int main() {
    try {
        test_uuid();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

