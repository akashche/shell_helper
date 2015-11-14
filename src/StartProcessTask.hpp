/* 
 * File:   StartProcessTask.hpp
 * Author: alex
 *
 * Created on November 14, 2015, 8:05 PM
 */

#ifndef SHELL_HELPER_STARTPROCESSTASK_HPP
#define	SHELL_HELPER_STARTPROCESSTASK_HPP

#include <string>

#include "staticlib/pimpl.hpp"

namespace shellhelper {

class StartProcessTask : public staticlib::pimpl::PimplObject {
protected:
    class Impl;

public:
    PIMPL_CONSTRUCTOR(StartProcessTask)

    StartProcessTask();

    uint32_t start_process(const std::string& desc_file);
};

} // namespace


#endif	/* SHELL_HELPER_STARTPROCESSTASK_HPP */

