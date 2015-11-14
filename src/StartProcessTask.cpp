/* 
 * File:   StartProcessTask.cpp
 * Author: alex
 * 
 * Created on November 14, 2015, 8:05 PM
 */

#include <string>
#include <vector>

#include "staticlib/utils.hpp"
#include "staticlib/io.hpp"
#include "staticlib/reflection.hpp"
#include "staticlib/serialization.hpp"
#include "staticlib/ranges.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "StartProcessTask.hpp"

namespace shellhelper {

namespace { // anonymous
namespace su = staticlib::utils;
namespace io = staticlib::io;
namespace sr = staticlib::reflection;
namespace ss = staticlib::serialization;
namespace ra = staticlib::ranges;
} // namespace

class StartProcessTask::Impl : public staticlib::pimpl::PimplObject::Impl {
public:
    Impl() { }

    uint32_t start_process(StartProcessTask&, const std::string& desc_file) {
        auto src = io::make_unbuffered_istreambuf(
                io::make_buffered_source(
                        su::FileDescriptor{desc_file, 'r'}));
        sr::ReflectedValue rv = ss::load_json(src);
        ProcessDesc pd{rv, desc_file};
        return su::exec_async(pd.executable, pd.arguments, pd.out_file);
    }
    
private:
    struct ProcessDesc {
        std::string executable;
        std::vector<std::string> arguments;
        std::string out_file;
        
        ProcessDesc(const sr::ReflectedValue& rv, const std::string& desc_file) {
            // check top-level type
            if (sr::ReflectedType::OBJECT != rv.get_type()) throw ShellHelperException(TRACEMSG(std::string() +
                    "Invalid process desc JSON file: [" + desc_file + "]," +
                    " top-level type: [" + sr::stringify_reflected_type(rv.get_type()) + "],"
                    " must be an 'OBJECT'"));
            // set fields
            for (auto& fi : rv.get_object()) {
                if ("executable" == fi.get_name()) {
                    this->executable = fi.get_string();
                } else if ("arguments" == fi.get_name()) {
                    auto refs = ra::refwrap(fi.get_array());
                    auto range = ra::transform(refs, [](const sr::ReflectedValue& val) {
                        return val.get_string();
                    });
                    ra::emplace_to(this->arguments, std::move(range));
                } else if ("out_file" == fi.get_name()) {
                    this->out_file = fi.get_string();
                }
            }
            // check fields
            if (this->executable.empty()) throw ShellHelperException(TRACEMSG(std::string() +
                    "Invalid process desc JSON file: [" + desc_file + "]," +
                    " 'executable' field not found"));
            if (this->out_file.empty()) throw ShellHelperException(TRACEMSG(std::string() +
                    "Invalid process desc JSON file: [" + desc_file + "]," +
                    " 'out_file' field not found"));
        }
    };

};
PIMPL_FORWARD_CONSTRUCTOR(StartProcessTask, (), (), ShellHelperException)
PIMPL_FORWARD_METHOD(StartProcessTask, uint32_t, start_process, (const std::string&), (), ShellHelperException)

} // namespace
