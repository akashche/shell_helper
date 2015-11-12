/* 
 * File:   shell_helper.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 12:50 PM
 */

#include <string>
#include <exception>
#include <iostream>

#include "tclap/CmdLine.h"

#include "UUIDTask.hpp"


int main(int argc, char** argv) {
    namespace tc = TCLAP;
    namespace sh = shellhelper;
    
    tc::CmdLine cline{"Shell Helper", ' ', "0.1"};
    tc::UnlabeledValueArg<std::string> task{"task", "Name of the task to perform", true, "", "task"};
    cline.add(task);
    cline.parse(argc, argv);
    if ("uuid" == task.getValue()) {
        std::cout << sh::UUIDTask::generate_uuid() << std::endl;
    } else {
        std::cerr << "ERROR: Invalid task specified: [" << task.getValue() <<  "], supported tasks:\n\n";
        std::cerr << "    - uuid: generate and print uuid";
        std::cerr << "\n\n";
        std::exit(1);
    }
    
    return 0;
}

