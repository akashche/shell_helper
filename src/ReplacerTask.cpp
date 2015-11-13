/* 
 * File:   ReplacerTask.cpp
 * Author: alex
 * 
 * Created on November 13, 2015, 8:25 PM
 */

#include <string>
#include <unordered_map>
#include <cstring>

#include "staticlib/utils.hpp"
#include "staticlib/io.hpp"
#include "staticlib/reflection.hpp"
#include "staticlib/serialization.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

#include "ShellHelperException.hpp"
#include "ReplacerTask.hpp"

namespace shellhelper {

namespace { // anonymous
namespace su = staticlib::utils;
namespace io = staticlib::io;
namespace sr = staticlib::reflection;
namespace ss = staticlib::serialization;
} // namespace

class ReplacerTask::Impl : public staticlib::pimpl::PimplObject::Impl {        
    
    std::string prefix;
    std::string postfix;
    size_t max_placeholder_len;
    
public:
    Impl(std::string prefix, std::string postfix, size_t max_placeholder_len) :
    prefix(std::move(prefix)),
    postfix(std::move(postfix)),
    max_placeholder_len(max_placeholder_len) { }

    void replace_files(ReplacerTask&, const std::string& src_file, const std::string& params_file,
            const std::string& dest_file) {
        auto params = read_params(params_file);
        Replacer rep{*this, src_file, dest_file, std::move(params), params_file};
        rep.replace();
    }
    
private:
    std::unordered_map<std::string, std::string> read_params(const std::string& params_file) {
        auto src = io::make_unbuffered_istreambuf(
                io::make_buffered_source(
                        su::FileDescriptor{params_file, 'r'}));
        sr::ReflectedValue rv = ss::load_json(src);
        if (sr::ReflectedType::OBJECT != rv.get_type()) throw ShellHelperException(TRACEMSG(std::string{} +
                "Invalid params JSON file: [" + params_file + "]," +
                " top-level type: [" + sr::stringify_reflected_type(rv.get_type()) + "],"
                " must be an 'OBJECT'"));
        std::unordered_map<std::string, std::string> map{};
        for (auto& fi : rv.get_object()) {
            if (sr::ReflectedType::STRING == fi.get_type()) {
                map.emplace(fi.get_name(), fi.get_string());
            } else throw ShellHelperException(TRACEMSG(std::string{} + 
                    "Invalid params JSON file: [" + params_file + "]," +
                    " field name: [" + fi.get_name() + "]" +
                    " has type: [" + sr::stringify_reflected_type(fi.get_type()) + "]," +
                    " must be a 'STRING'"));
        }
        return map;
    }

    
    
    class Replacer {
        enum class State { PREFIX, PLACEHOLDER };
        
        ReplacerTask::Impl& parent;
        
        io::buffered_source<su::FileDescriptor> src;
        io::buffered_sink<su::FileDescriptor> dest;
        std::unordered_map<std::string, std::string> params;
        const std::string& params_file;

        std::string placeholder{};
        State state = State::PREFIX;
        size_t ind_prefix = 0;
        size_t ind_postfix = 0;
        
    public:    
        Replacer(ReplacerTask::Impl& parent, const std::string& src_file, 
                const std::string& dest_file, std::unordered_map<std::string, std::string>&& params,
                const std::string& params_file) :
        parent(parent),
        src(su::FileDescriptor{src_file, 'r'}),
        dest(su::FileDescriptor{dest_file, 'w'}),
        params(std::move(params)),
        params_file(params_file){ }
        
        void replace() {
            char cur;
            while (std::char_traits<char>::eof() != src.read(std::addressof(cur), 1)) {
                switch (state) {
                case State::PREFIX:
                    do_prefix(cur);
                    break;
                case State::PLACEHOLDER:
                    do_placeholder(cur);
                    break;
                }
            }
            if (placeholder.length() > 0) throw ShellHelperException(TRACEMSG(std::string() +
                    "Invalid unclosed placeholder: [" + placeholder +"]"
                    " at the end of the source file: [" + src.get_source().get_file_path() + "]"));
        }
                
    private:
        void do_prefix(char cur) {
            if (cur != parent.prefix[ind_prefix]) {
                if (ind_prefix > 0) {
                    dest.write(parent.prefix.c_str(), ind_prefix);  
                    ind_prefix = 0;
                }
                dest.write(std::addressof(cur), 1);
            } else {
                ind_prefix += 1;
                if (parent.prefix.length() == ind_prefix) {
                    ind_prefix = 0;
                    state = State::PLACEHOLDER;
                }
            }
        }
        
        void do_placeholder(char cur) {
            placeholder.push_back(cur);
            if (placeholder.size() == parent.max_placeholder_len) throw ShellHelperException(TRACEMSG(std::string() +
                    "Parameter name: [" + placeholder + "] is too long"
                    " in source file: [" + src.get_source().get_file_path() + "]," +
                    " max allowed length: [" + su::to_string(parent.max_placeholder_len - parent.postfix.size()) + "]"));
            if (cur == parent.postfix[ind_postfix]) {
                ind_postfix += 1;
                if (parent.postfix.length() == ind_postfix) {
                    ind_postfix = 0;
                    placeholder.resize(placeholder.length() - parent.postfix.length());
                    auto par = params.find(placeholder);
                    if (params.end() != par) {
                        dest.write(par->second.data(), par->second.size());
                        placeholder.clear();
                        state = State::PREFIX;
                    } else throw ShellHelperException(TRACEMSG(std::string() +
                            "Parameter: [" + placeholder + "] not found" +
                            " in params file: [" + params_file + "]"));
                }
            } else {
                ind_postfix = 0;
            }
        }

    };

};
PIMPL_FORWARD_CONSTRUCTOR(ReplacerTask, (std::string)(std::string)(size_t), (), ShellHelperException)
PIMPL_FORWARD_METHOD(ReplacerTask, void, replace_files, (const std::string&)(const std::string&)
        (const std::string&), (), ShellHelperException)

} // namespace

