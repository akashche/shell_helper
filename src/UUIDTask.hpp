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

/**
 * Implements 'uuid' task
 */
class UUIDTask : public staticlib::pimpl::PimplObject {
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
    PIMPL_CONSTRUCTOR(UUIDTask)            
       
    /**
     * Constructor
     */
    UUIDTask();
    
    /**
     * Generates new UUID and returns it as a string
     * 
     * @return UUID as a string
     */
    std::string generate_uuid();
};

} // namespace

#endif	/* SHELL_HELPER_UUIDTASK_HPP */

