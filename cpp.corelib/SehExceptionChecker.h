#pragma once
#include "exp.h"
#include <windows.h>
#include <eh.h>

namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API SehExceptionChecker
        {
        public:
            enum RemindFunc {
                ConsoleFunc = 0x1,
                MsgBoxFunc = 0x2
            };
        public:
            static void init(RemindFunc func = ConsoleFunc);
            static void SetSehTranslator(_se_translator_function _NewSETranslator);
            static void SetTopExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
        private:
            static RemindFunc remindFunc;
            static _se_translator_function _NewSETranslator;
            static LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter;
            static void TransFunc(unsigned int u, EXCEPTION_POINTERS* pExp);
            static long __stdcall TopExceptionFilter(_EXCEPTION_POINTERS* lpExceptionInfo);
        };
    }
}


