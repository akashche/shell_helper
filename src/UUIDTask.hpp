/* 
 * File:   UUIDTask.hpp
 * Author: alex
 *
 * Created on November 12, 2015, 1:15 PM
 */

#ifndef SHELL_HELPER_UUIDTASK_HPP
#define	SHELL_HELPER_UUIDTASK_HPP

#include <string>

#include "staticlib/pimpl.hpp"

namespace shellhelper {

class UUIDTask : public staticlib::pimpl::PimplObject {
protected:
    class Impl;    
    
public:
    PIMPL_CONSTRUCTOR(UUIDTask)
            
    UUIDTask();
    
    std::string generate_uuid();
};

} // namespace

#endif	/* SHELL_HELPER_UUIDTASK_HPP */

