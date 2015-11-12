/* 
 * File:   CurrentDateTask.hpp
 * Author: alex
 *
 * Created on November 12, 2015, 1:15 PM
 */

#ifndef SHELL_HELPER_CURRENTDATETASK_HPP
#define	SHELL_HELPER_CURRENTDATETASK_HPP

#include <string>

#include "staticlib/pimpl.hpp"

namespace shellhelper {

class CurrentDateTask : public staticlib::pimpl::PimplObject {
protected:
    class Impl;

public:
    PIMPL_CONSTRUCTOR(CurrentDateTask)

    CurrentDateTask();
            
    std::string current_date(const std::string& format = "%Y-%m-%d %H:%M:%S");
};

} // namespace

#endif	/* SHELL_HELPER_CURRENTDATETASK_HPP */

