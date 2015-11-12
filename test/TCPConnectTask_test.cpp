/* 
 * File:   TCPConnectTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 9:01 PM
 */

#include <string>
#include <iostream>
#include <cstdint>
#include <cassert>

#include "TCPConnectTask.hpp"

int main() {
    namespace sh = shellhelper;
    
    sh::TCPConnectTask tct{};
    
//    std::string success = tct.check_connection("127.0.0.1", 22);
//    (void) success;
//    assert(success.empty());

    std::string fail = tct.check_connection("127.0.0.1", 1234);
    (void) fail;
    assert(!fail.empty());
    
    return 0;
}

