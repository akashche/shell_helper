/* 
 * File:   CurrentDateTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 4:04 PM
 */

#include <string>
#include <iostream>
#include <cassert>

#include "CurrentDateTask.hpp"


int main() {
    namespace sh = shellhelper;

    std::string st = sh::CurrentDateTask().current_date();
    std::cout << st << std::endl;
    (void) st;
    assert(st.length() > 0);

    return 0;
}

