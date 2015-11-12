/* 
 * File:   UUIDTask.cpp
 * Author: alex
 * 
 * Created on November 12, 2015, 1:15 PM
 */

#include "guid.h"

#include "staticlib/utils.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "UUIDTask.hpp"
#include "ShellHelperException.hpp"

namespace shellhelper {

namespace { // anonymous
namespace su = staticlib::utils;
} // namespace

class UUIDTask::Impl : public staticlib::pimpl::PimplObject::Impl {
public:
    static std::string generate_uuid() {
        auto guid = GuidGenerator().newGuid();
        return su::to_string(guid);
    }
    
};
PIMPL_FORWARD_METHOD_STATIC(UUIDTask, std::string, generate_uuid, (), (), ShellHelperException)

} // namespace
