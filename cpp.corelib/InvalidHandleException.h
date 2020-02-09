#pragma once
#include "exp.h"
#include "Exception.h"
namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API InvalidHandleException
            : public Exception
        {
        public:
            InvalidHandleException();
            InvalidHandleException(_EXCEPTION_POINTERS* exp);
            ~InvalidHandleException();
        };
    }
}

