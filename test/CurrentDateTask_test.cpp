/* 
 * File:   CurrentDateTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 4:04 PM
 */

#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"

#include "CurrentDateTask.hpp"

namespace sh = shellhelper;

void test_current_date() {
    std::string st = sh::CurrentDateTask().current_date();
    std::cout << st << std::endl;
    slassert(st.length() > 0);
}

int main() {
    try {
        test_current_date();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

