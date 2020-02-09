#pragma once
#include "exp.h"
#include <string>
#include <stdexcept>
#include "CallStack.h"
using namespace std;
namespace cpp
{
    namespace corelib {
        class CPPCORELIB_API Exception
            : public std::exception
        {
        public:
            Exception(string name);
            Exception(_EXCEPTION_POINTERS* exp, string name = "Exception");
            void AppendMessage(string msg);
            ~Exception();
            virtual char const* what() const;
        protected:
            string name;
            string msgStr;
            CallStack::callstack_ptr pCall = nullptr;
            string traceStack() const;
        };
    }
}

