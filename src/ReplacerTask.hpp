/* 
 * File:   ReplacerTask.hpp
 * Author: alex
 *
 * Created on November 13, 2015, 8:25 PM
 */

#ifndef SHELL_HELPER_REPLACERTASK_HPP
#define	SHELL_HELPER_REPLACERTASK_HPP

#include <string>

#include "staticlib/pimpl.hpp"

namespace shellhelper {

class ReplacerTask : public staticlib::pimpl::PimplObject {
protected:
    class Impl;

public:
    PIMPL_CONSTRUCTOR(ReplacerTask)

    ReplacerTask(std::string prefix = "{{", std::string postfix = "}}", size_t max_placeholder_len = 255);

    void replace_files(const std::string& src_file, const std::string& params_file, 
            const std::string& dest_file);
};

} // namespace

#endif	/* SHELL_HELPER_REPLACERTASK_HPP */

