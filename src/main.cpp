/* 
 * File:   shell_helper.cpp
 * Author: alex
 *
 * Created on November 12, 2015, 12:50 PM
 */

#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <functional>
#include <cstdint>

#include "tclap/CmdLine.h"

#include "UUIDTask.hpp"
#include "CurrentDateTask.hpp"
#include "TCPConnectTask.hpp"
#include "ReplacerTask.hpp"

namespace { // anonymous

namespace tc = TCLAP;
namespace sh = shellhelper;

void validate_arg_set(const std::string& task, std::vector<tc::Arg*> args)  {
    for (auto arg : args) {
        if (!arg->isSet()) {
            std::cerr << "\nERROR: [" + arg->getName() + "] option must be specified for [" + task + "] task\n\n";
            std::exit(1);
        }
    }
}

void task_name_error(const std::string& task) {
    std::cerr << "\nERROR: Invalid task specified: [" << task << "], supported tasks:\n\n";
    std::cerr << "    - uuid: generate and print uuid\n\n";
    std::cerr << "    - time: print current time using specified 'time_format' (optional)\n\n";
    std::cerr << "    - connect: test connection to specified 'connect_ip' address and 'connect_port'\n\n";
    std::cerr << "    - replace: replaces the placeholders in 'replace_source' file with the data\n" <<
                 "      from the 'replace_params' file and writes the results into 'replace_dest' file\n\n";
    std::exit(1);
}

int launch(int argc, char** argv) {
    // options
    tc::CmdLine cline{"Shell Helper", ' ', "0.1"};
    tc::UnlabeledValueArg<std::string> task{"task", "Name of the task to perform", true, "", "task"};
    cline.add(task);
    tc::ValueArg<std::string> time_format{"f", "time_format", "[time] Datetime format", false, "%Y-%m-%d %H:%M:%S", "time_format"};
    cline.add(time_format);
    tc::ValueArg<std::string> connect_ip{"i", "connect_ip", "[connect] IP address to test connection", false, "", "connect_ip"};
    cline.add(connect_ip);
    tc::ValueArg<uint16_t> connect_port{"p", "connect_port", "[connect] TCP port to test connection", false, 0, "connect_port"};
    cline.add(connect_port);
    tc::ValueArg<std::string> replace_source{"", "replace_source", "[replace] Source file for 'replace' task", false, "", "replace_source"};
    cline.add(replace_source);
    tc::ValueArg<std::string> replace_params{"", "replace_params", "[replace] Params JSON file for 'replace' task", false, "", "replace_params"};
    cline.add(replace_params);
    tc::ValueArg<std::string> replace_dest{"", "replace_dest", "[replace] Destination file for the 'replace' task", false, "", "replace_dest"};
    cline.add(replace_dest);
    // process
    cline.parse(argc, argv);
    // generate UUID
    if ("uuid" == task.getValue()) {
        std::cout << sh::UUIDTask().generate_uuid() << std::endl;
        // print current datetime    
    } else if ("time" == task.getValue()) {
        std::cout << sh::CurrentDateTask().current_date(time_format.getValue()) << std::endl;
        // test TCP connection
    } else if ("connect" == task.getValue()) {
        validate_arg_set(task.getValue(), {&connect_ip, &connect_port});
        std::string err = sh::TCPConnectTask().check_connection(connect_ip.getValue(), connect_port.getValue());
        if (!err.empty()) {
            std::cout << err << std::endl;
            std::exit(1);
        }
        std::cout << "SUCCESS" << std::endl;
    } else if ("replace" == task.getValue()) {
        validate_arg_set(task.getValue(), {&replace_source, &replace_params, &replace_dest});
        sh::ReplacerTask().replace_files(replace_source.getValue(), replace_params.getValue(),
                replace_dest.getValue());
    } else {
        task_name_error(task.getValue());
    }

    return 0;
}

} // namespace

int main(int argc, char** argv) {
    try {
        return launch(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } 
}

