/* 
 * File:   UUIDTask_test.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 3:11 PM
 */

#include <string>
#include <cassert>

#include "UUIDTask.hpp"

int main() {
    namespace sh = shellhelper;
    
    std::string uuid = sh::UUIDTask::generate_uuid();
    (void) uuid;
    assert(uuid.length() > 0);

    return 0;
}

