#include "stdafx.h"
#include "WindowsException.h"
namespace cpp
{
    namespace corelib
    {
        WindowsException::WindowsException(DWORD errCode)
            : Exception("WindowsException")
        {
            AppendMessage(" : " + getErrorMessage(errCode));
        }


        WindowsException::WindowsException(_EXCEPTION_POINTERS* exp, DWORD errCode)
            : Exception(exp, "WindowsException")
        {
            AppendMessage(" : " + getErrorMessage(errCode));
        }

        WindowsException::~WindowsException()
        {
        }

        std::string WindowsException::getErrorMessage(DWORD errCode)
        {
            DWORD languageID = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
            HLOCAL hlocal = NULL;
            BOOL fOk = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, errCode, languageID, (LPSTR)&hlocal, 0, NULL);
            if (!fOk) {
                HMODULE hDll = LoadLibraryExA("netmsg.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);
                if (hDll != NULL) {
                    FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM, hDll, errCode, languageID, (LPSTR)&hlocal, 0, NULL);
                    FreeLibrary(hDll);
                }
            }
            string str((char*)LocalLock(hlocal));
            LocalFree(hlocal);
            return str;
        }

        
    }
}

