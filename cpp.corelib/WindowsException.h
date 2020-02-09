#pragma once
#include "exp.h"
#include "Exception.h"
namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API WindowsException
            : public Exception
        {
        public:
            WindowsException(DWORD errCode = GetLastError());
            WindowsException( _EXCEPTION_POINTERS* exp, DWORD errCode = GetLastError());
            ~WindowsException();
        protected:
            static string getErrorMessage(DWORD errCode);
        };

    }
}

