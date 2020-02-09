#include "stdafx.h"
#include "SehExceptionChecker.h"
#include "DivideByZeroException.h"
#include "AccessViolationException.h"
#include "InvalidHandleException.h"
#include <DbgHelp.h>
#include <sstream>
#include <iostream>
using namespace std;
#pragma comment(lib, "DbgHelp.lib")

namespace cpp
{
    namespace corelib
    {
        SehExceptionChecker::RemindFunc SehExceptionChecker::remindFunc = RemindFunc::ConsoleFunc;
        
        void SehExceptionChecker::init(RemindFunc func)
        {
            remindFunc = func;
            SetSehTranslator(TransFunc);
            SetTopExceptionFilter(TopExceptionFilter);
        }

        void SehExceptionChecker::SetSehTranslator(_se_translator_function _NewSETranslator)
        {
            _NewSETranslator = _NewSETranslator;
            _set_se_translator(_NewSETranslator);
        }

        void SehExceptionChecker::SetTopExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
        {
            lpTopLevelExceptionFilter = lpTopLevelExceptionFilter;
            SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
        }

        void SehExceptionChecker::TransFunc(unsigned int u, EXCEPTION_POINTERS* pExp)
        {
            HANDLE process = GetCurrentProcess();
            SymInitialize(process, NULL, TRUE);
            switch (pExp->ExceptionRecord->ExceptionCode)
            {
            case EXCEPTION_ACCESS_VIOLATION:
            {
                throw AccessViolationException(pExp);
            }
            break;
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
            {
                throw DivideByZeroException(pExp);
            }
            break;
            case EXCEPTION_INVALID_HANDLE:
            {
                throw InvalidHandleException(pExp);
            }
            break;
            default:
            {
                throw Exception(pExp);
            }
            break;
            }
        }

        long __stdcall SehExceptionChecker::TopExceptionFilter(_EXCEPTION_POINTERS* lpExceptionInfo)
        {
            HANDLE process = GetCurrentProcess();
            SymInitialize(process, NULL, TRUE);
            try
            {
                switch (lpExceptionInfo->ExceptionRecord->ExceptionCode)
                {
                case EXCEPTION_ACCESS_VIOLATION:
                {
                    throw AccessViolationException(lpExceptionInfo);
                }
                break;
                case EXCEPTION_INT_DIVIDE_BY_ZERO:
                {
                    throw DivideByZeroException(lpExceptionInfo);
                }
                break;
                case EXCEPTION_INVALID_HANDLE:
                {
                    throw InvalidHandleException(lpExceptionInfo);
                }
                break;
                default:
                {
                    throw Exception(lpExceptionInfo);
                }
                break;
                }
            }
            catch (const Exception& e)
            {
                switch (remindFunc)
                {
                case cpp::corelib::SehExceptionChecker::ConsoleFunc:
                    cout << e.what() << endl;
                    break;
                case cpp::corelib::SehExceptionChecker::MsgBoxFunc:
                    ::MessageBoxA(0, e.what(), "未经处理的异常", 0);
                    break;
                default:
                    break;
                }
            }
            return EXCEPTION_EXECUTE_HANDLER;
        }

    }
}

