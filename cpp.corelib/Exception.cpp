#include "stdafx.h"
#include "Exception.h"
#include <sstream>

namespace cpp {
    namespace corelib {

        Exception::Exception(string name)
        {
            this->name = name;
            pCall = CallStack::generate();
            msgStr = traceStack();
        }

        Exception::Exception(_EXCEPTION_POINTERS* exp, string name /*= "Exception"*/)
        {
            this->name = name;
            pCall = CallStack::generate(exp->ContextRecord);
            msgStr = traceStack();
        }

        void Exception::AppendMessage(string msg)
        {
            this->name += msg;
            msgStr = traceStack();
        }

        Exception::~Exception()
        {
        }

        char const* Exception::what() const
        {
            return msgStr.c_str();
        }

        std::string Exception::traceStack() const
        {
            std::ostringstream oss;
            oss << this->name << endl;
            for (CallStack::const_iterator it = pCall->begin(); it != pCall->end(); ++it)
                oss << *it << endl;
            return oss.str();
        }

    }
}