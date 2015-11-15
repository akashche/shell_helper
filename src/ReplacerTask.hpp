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

/**
 * Implements 'replace' task
 */
class ReplacerTask : public staticlib::pimpl::PimplObject {
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
    PIMPL_CONSTRUCTOR(ReplacerTask)

    /**
     * Constructor
     * 
     * @param prefix placeholder prefix string, `{{` by default
     * @param postfix placeholder postfix string, `}}` by default
     * @param max_placeholder_len max length of the placeholder, `255` by default
     */
    ReplacerTask(std::string prefix = "{{", std::string postfix = "}}", size_t max_placeholder_len = 255);

    /**
     * Replaces placeholder in source file using params from JSON file
     * and writes results to dest file
     * 
     * @param src_file source file with placeholders
     * @param params_file JSON file with parameters
     * @param dest_file out file
     */
    void replace_files(const std::string& src_file, const std::string& params_file, 
            const std::string& dest_file);
};

} // namespace

#endif	/* SHELL_HELPER_REPLACERTASK_HPP */

