/* 
 * File:   ReplacerTask_test.cpp
 * Author: alex
 *
 * Created on November 13, 2015, 10:19 PM
 */

#include <string>
#include <array>
#include <cassert>

#include "staticlib/utils.hpp"
#include "staticlib/io.hpp"
#include "staticlib/reflection.hpp"
#include "staticlib/serialization.hpp"

#include "ReplacerTask.hpp"

namespace su = staticlib::utils;
namespace io = staticlib::io;
namespace sr = staticlib::reflection;
namespace ss = staticlib::serialization;
namespace sh = shellhelper;

const std::string SRC_FILE = "ReplacerTask_test_src.txt";
const std::string PARAMS_FILE = "ReplacerTask_test_params.txt";
const std::string DEST_FILE = "ReplacerTask_test_dest.txt";

void write_src_data() {
    su::FileDescriptor src{SRC_FILE, 'w'};
    std::string data{"41 {{foo}} 43 {{bar}}"};
    src.write(data.c_str(), data.length());
}

void write_params() {
    auto sink = io::make_unbuffered_ostreambuf(
            su::FileDescriptor{PARAMS_FILE, 'w'});
    sr::ReflectedValue params{
        {"foo", "42"},
        {"bar", "44"}};
    ss::dump_json(params, sink);
}

void test_replace() {
    write_src_data();
    write_params();
    sh::ReplacerTask task{};
    task.replace_files(SRC_FILE, PARAMS_FILE, DEST_FILE);
    su::FileDescriptor dest{DEST_FILE, 'r'};
    io::string_sink sink{};
    std::array<char, 8192> buf;
    io::copy_all(dest, sink, buf.data(), buf.size());
    assert("41 42 43 44" == sink.get_string());
}

int main() {
    test_replace();

    return 0;
}

