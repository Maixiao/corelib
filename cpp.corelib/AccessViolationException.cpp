#include "stdafx.h"
#include "AccessViolationException.h"

namespace cpp
{
    namespace corelib
    {
        AccessViolationException::AccessViolationException()
            : Exception("AccessViolationException")
        {
        }


        AccessViolationException::AccessViolationException(_EXCEPTION_POINTERS* exp)
            : Exception(exp, "AccessViolationException")
        {

        }

        AccessViolationException::~AccessViolationException()
        {
        }
    }
    
}