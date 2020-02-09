#pragma once
#include "exp.h"
#include "Exception.h"
namespace cpp
{
    namespace corelib {
        class CPPCORELIB_API DivideByZeroException
            : public Exception
        {
        public:
            DivideByZeroException();
            DivideByZeroException(_EXCEPTION_POINTERS* exp);
            ~DivideByZeroException();
        };

    }
}

