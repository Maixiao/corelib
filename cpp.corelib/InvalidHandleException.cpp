#include "stdafx.h"
#include "InvalidHandleException.h"

namespace cpp
{
    namespace corelib
    {
        InvalidHandleException::InvalidHandleException()
            : Exception("InvalidHandleException")
        {
        }


        InvalidHandleException::InvalidHandleException(_EXCEPTION_POINTERS* exp):
            Exception(exp, "InvalidHandleException")
        {

        }

        InvalidHandleException::~InvalidHandleException()
        {
        }
    }

}

