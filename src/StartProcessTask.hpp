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

/**
 * Implements 'process' task
 */
class StartProcessTask : public staticlib::pimpl::PimplObject {
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
    PIMPL_CONSTRUCTOR(StartProcessTask)

    /**
     * Constuctor
     */
    StartProcessTask();

    /**
     * Starts process in background using details from specified JSON file
     * 
     * @param desc_file JSON file with process description
     * @return process PID
     */
    uint32_t start_process(const std::string& desc_file);
};

} // namespace


#endif	/* SHELL_HELPER_STARTPROCESSTASK_HPP */

