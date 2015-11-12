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
#include "CurrentDateTask.hpp"


int main(int argc, char** argv) {
    namespace tc = TCLAP;
    namespace sh = shellhelper;
    
    tc::CmdLine cline{"Shell Helper", ' ', "0.1"};
    tc::UnlabeledValueArg<std::string> task{"task", "Name of the task to perform", true, "", "task"};
    tc::ValueArg<std::string> time_format{"f", "time_format", "[time] Datetime format", false, "%Y-%m-%d %H:%M:%S", "time_format"};
    cline.add(task);
    cline.add(time_format);
    cline.parse(argc, argv);
    if ("uuid" == task.getValue()) {
        std::cout << sh::UUIDTask().generate_uuid() << std::endl;
    } else if("time" == task.getValue()) {
        std::cout << sh::CurrentDateTask().current_date(time_format.getValue()) << std::endl;
    } else {
        std::cerr << "\nERROR: Invalid task specified: [" << task.getValue() <<  "], supported tasks:\n\n";
        std::cerr << "    - uuid: generate and print uuid\n\n";
        std::cerr << "    - time: print current time\n\n";
        std::exit(1);
    }
    
    return 0;
}

