#include "stdafx.h"
#include "CallStackImp.h"
#include <Psapi.h>
#include <DbgHelp.h>
#pragma comment( lib, "Dbghelp.lib" )
#pragma comment( lib, "Psapi.lib" )
using namespace std;

namespace cpp {
    namespace corelib {
        bool CallStackImp::m_bInitialized = false;

        CallStackImp::CallStackImp()
        {
            if (!m_bInitialized)
            {
                _initialize();
            }
        }


        CallStackImp::~CallStackImp()
        {
        }

        CallStackImp::const_iterator CallStackImp::begin() const
        {
            return m_lstFunc.begin();
        }

        CallStackImp::const_iterator CallStackImp::end() const
        {
            return m_lstFunc.end();
        }

        CallStackImp::callstack_ptr CallStackImp::generate(const void* pContext)
        {
            if (!m_bInitialized)
            {
                _initialize();
            }

            CONTEXT Context;

            if (pContext != NULL)
            {
                ::memcpy_s(&Context, sizeof(CONTEXT), pContext, sizeof(CONTEXT));
            }
            else
            {
                ::ZeroMemory(&Context, sizeof(Context));
                Context.ContextFlags = CONTEXT_FULL;

                __asm
                {
                    call FakeFuncCall
                    FakeFuncCall :

                    pop eax
                        mov Context.Eip, eax
                        mov Context.Ebp, ebp
                        mov Context.Esp, esp
                }
            }

            static const int gc_iMaxStackDepth = 512;
            QWORD aryStack[gc_iMaxStackDepth] = { 0 };

            // 由于_stackwalk内部使用SEH 因此不能在其内部使用C++类
            _stackwalk(aryStack, gc_iMaxStackDepth, &Context);


            callstack_ptr spCallStack(new CallStack());


            for (int i = 0; i < gc_iMaxStackDepth && aryStack[i] != 0; ++i)
            {
                func_name name = _getfuncname(aryStack[i]);
                spCallStack->m_spImp->m_lstFunc.push_back(name);
            }
            return spCallStack;
        }

        void CallStackImp::_initialize()
        {
            if (m_bInitialized)
            {
                return;
            }

            // 设置符号引擎
            DWORD SymOpts = ::SymGetOptions();
            SymOpts |= SYMOPT_LOAD_LINES;
            SymOpts |= SYMOPT_DEBUG;
            ::SymSetOptions(SymOpts);

            if (FALSE == ::SymInitialize(::GetCurrentProcess(), NULL, TRUE))
            {
                // DBSOFT_LogMsg( "::SymInitialize初始化失败..." );
                return;
            }

            if (!_loadAllModules())
            {
                // DBSOFT_LogMsg( "LoadModules发生了错了" );
            }

            m_bInitialized = true;
        }

        bool CallStackImp::_loadAllModules()
        {
            HANDLE                 hProcess = ::GetCurrentProcess();
            static const int       gc_iMaxHandles = 4096;
            HMODULE                aryHandles[gc_iMaxHandles] = { 0 };

            unsigned               uBytes = 0;

            BOOL bResult = ::EnumProcessModules(
                hProcess, aryHandles, sizeof(aryHandles), (LPDWORD)&uBytes);

            if (FALSE == bResult)
            {
                // DBSOFT_LogMsg( "::EnumProcessModules失败 Msg:", GetLastErrorDescA() );
                return false;
            }

            const int iCount = uBytes / sizeof(HMODULE);

            for (int i = 0; i < iCount; ++i)
            {
                char szModuleName[4096] = { 0 };
                char szImageName[4096] = { 0 };
                MODULEINFO Info;

                ::GetModuleInformation(hProcess, aryHandles[i], &Info, sizeof(Info));
                ::GetModuleFileNameExA(hProcess, aryHandles[i], szImageName, 4096);
                ::GetModuleBaseNameA(hProcess, aryHandles[i], szModuleName, 4096);

                DWORD m = ::SymLoadModule64(hProcess, aryHandles[i], szImageName, szModuleName, (DWORD64)Info.lpBaseOfDll, (DWORD)Info.SizeOfImage);
            }

            return true;
        }

        void CallStackImp::_stackwalk(QWORD* pTrace, DWORD dwMaxDepth, CONTEXT* pContext)
        {
            STACKFRAME64        sfStackFrame64;
            HANDLE              hProcess = ::GetCurrentProcess();
            HANDLE              hThread = ::GetCurrentThread();

            DWORD               dwDepth = 0;

            ::ZeroMemory(&sfStackFrame64, sizeof(sfStackFrame64));

            __try
            {
                sfStackFrame64.AddrPC.Offset = pContext->Eip;
                sfStackFrame64.AddrPC.Mode = AddrModeFlat;
                sfStackFrame64.AddrStack.Offset = pContext->Esp;
                sfStackFrame64.AddrStack.Mode = AddrModeFlat;
                sfStackFrame64.AddrFrame.Offset = pContext->Ebp;
                sfStackFrame64.AddrFrame.Mode = AddrModeFlat;

                bool bSuccessed = true;

                while (bSuccessed && (dwDepth < dwMaxDepth))
                {
                    bSuccessed = ::StackWalk64(
                        IMAGE_FILE_MACHINE_I386,
                        hProcess,
                        hThread,
                        &sfStackFrame64,
                        pContext,
                        NULL,
                        SymFunctionTableAccess64,
                        SymGetModuleBase64,
                        NULL
                    ) != FALSE;

                    pTrace[dwDepth] = sfStackFrame64.AddrPC.Offset;
                    ++dwDepth;

                    if (!bSuccessed)
                    {
                        break;
                    }

                    if (sfStackFrame64.AddrFrame.Offset == 0)
                    {
                        break;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        CallStackImp::func_name CallStackImp::_getfuncname(QWORD dwFunc)
        {
            static const int gc_iMaxNameLength = 4096;
            char                    szSymbol[sizeof(IMAGEHLP_SYMBOL64) + gc_iMaxNameLength] = { 0 };
            PIMAGEHLP_SYMBOL64      Symbol;
            DWORD                   dwSymbolDisplacement = 0;
            DWORD64                 dw64SymbolDisplacement = 0;

            HANDLE                  hProcess = ::GetCurrentProcess();

            Symbol = (PIMAGEHLP_SYMBOL64)szSymbol;
            Symbol->SizeOfStruct = sizeof(szSymbol);
            Symbol->MaxNameLength = gc_iMaxNameLength;

            func_name              strResult = "\tat ";
            if (::SymGetSymFromAddr64(
                hProcess,
                dwFunc,
                &dw64SymbolDisplacement,
                Symbol)
                )
            {
                int i = 0;
                for (; Symbol->Name[i] < 32 || Symbol->Name[i] > 127; )
                {
                    ++i;
                }

                strResult += (const char*)(Symbol->Name + i);
            }
            else
            {
                strResult += "unknown";
                return strResult;
            }

            IMAGEHLP_LINE64            ImageHelpLine;
            ImageHelpLine.SizeOfStruct = sizeof(ImageHelpLine);


            IMAGEHLP_MODULE64 ImageHelpModule;
            ImageHelpModule.SizeOfStruct = sizeof(ImageHelpModule);

            char szModuleName[1024] = { 0 };
            string strModuleName, strFileInfo;
            if (::SymGetModuleInfo64(hProcess, dwFunc, &ImageHelpModule))
            {
                strModuleName = string(ImageHelpModule.ImageName);
                strModuleName = strModuleName.substr(strModuleName.rfind("\\") + 1);
                char szBuf[4096] = { 0 };
                sprintf_s(szBuf, "%s+0x%X", strModuleName.c_str(), dwFunc);
                strModuleName = string(szBuf);
            }
            if (::SymGetLineFromAddr64(hProcess, dwFunc, &dwSymbolDisplacement, &ImageHelpLine))
            {
                char szBuf[4096] = { 0 };
                sprintf_s(szBuf, "%s:%d", ImageHelpLine.FileName, ImageHelpLine.LineNumber);
                strFileInfo = string(szBuf);
            }

            strResult += "(";
            if (strFileInfo != "")
            {
                strResult += strFileInfo;
            }
            else
            {
                strResult += strModuleName;
            }
            strResult += ")";
            return strResult;
        }

    }
}
