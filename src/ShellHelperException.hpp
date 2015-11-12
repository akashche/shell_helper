/* 
 * File:   ShellHelperException.hpp
 * Author: alex
 *
 * Created on November 12, 2015, 1:28 PM
 */

#ifndef SHELL_HELPER_SHELLHELPEREXCEPTION_HPP
#define	SHELL_HELPER_SHELLHELPEREXCEPTION_HPP

#include "staticlib/utils/BaseException.hpp"

namespace shellhelper {

/**
 * Module specific exception
 */
class ShellHelperException : public staticlib::utils::BaseException {
public:
    /**
     * Default constructor
     */
    ShellHelperException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    ShellHelperException(const std::string& msg) :
    staticlib::utils::BaseException(msg) { }

};

} //namespace

#endif	/* SHELL_HELPER_SHELLHELPEREXCEPTION_HPP */

