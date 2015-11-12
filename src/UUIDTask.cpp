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
