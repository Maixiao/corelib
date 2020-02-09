#include "stdafx.h"
#include "DivideByZeroException.h"

namespace cpp
{
    namespace corelib {
        DivideByZeroException::DivideByZeroException()
            : Exception("DivideByZeroException")
        {
        }


        DivideByZeroException::DivideByZeroException(_EXCEPTION_POINTERS* exp)
            : Exception(exp, "DivideByZeroException")
        {

        }

        DivideByZeroException::~DivideByZeroException()
        {
        }
    }
}

