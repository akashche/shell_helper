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

/**
 * Implements 'time' task
 */
class CurrentDateTask : public staticlib::pimpl::PimplObject {
protected:
    /**
     * Implementation class declaration
     */
    class Impl;

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(CurrentDateTask)

    /**
     * Constructor
     */
    CurrentDateTask();
    
    /**
     * Returns current date and time formatted as a string using
     * specified format string
     * 
     * @param format format string
     * @return formatted date and time
     */
    std::string current_date(const std::string& format = "%Y-%m-%d %H:%M:%S");
};

} // namespace

#endif	/* SHELL_HELPER_CURRENTDATETASK_HPP */

