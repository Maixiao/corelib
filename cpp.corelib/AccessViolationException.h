#pragma once
#include "exp.h"
#include "Exception.h"
namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API AccessViolationException
            : public Exception
        {
        public:
            AccessViolationException();
            AccessViolationException(_EXCEPTION_POINTERS* exp);
            ~AccessViolationException();
        };
    }
}
