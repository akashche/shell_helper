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
 * File:   UUIDTask.cpp
 * Author: alex
 * 
 * Created on November 12, 2015, 1:15 PM
 */

#include "guid.h"

#include "staticlib/utils.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "UUIDTask.hpp"

namespace shellhelper {

namespace { // anonymous
namespace su = staticlib::utils;
} // namespace

class UUIDTask::Impl : public staticlib::pimpl::PimplObject::Impl {
    GuidGenerator gen;
    
public:
    Impl() { }
    
    std::string generate_uuid(UUIDTask&) {
        auto guid = gen.newGuid();
        return su::to_string(guid);
    }
    
};
PIMPL_FORWARD_CONSTRUCTOR(UUIDTask, (), (), ShellHelperException)
PIMPL_FORWARD_METHOD(UUIDTask, std::string, generate_uuid, (), (), ShellHelperException)

} // namespace
