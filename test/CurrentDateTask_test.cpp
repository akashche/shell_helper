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

