#pragma once
#include "exp.h"
#include "CallStack.h"
#include <windows.h>
#include <WinDNS.h>
#include <string>
#include <list>
#include <memory>

namespace cpp {
    namespace corelib {
        class CPPCORELIB_API CallStackImp
        {
        public:
            friend class CallStack;
        public:
            typedef std::string             func_name;
            typedef std::list< func_name >                 func_name_list;
            typedef func_name_list::const_iterator         const_iterator;
            typedef std::shared_ptr<CallStack>        callstack_ptr;
        public:
            CallStackImp();
            ~CallStackImp();
        public:
            const_iterator begin() const;
            const_iterator end() const;
        public:
            static callstack_ptr generate(const void* pContext);
        protected:
            static void _initialize();
            static bool           _loadAllModules();
            static void           _stackwalk(QWORD* pTrace, DWORD dwMaxDepth, CONTEXT* pContext);
            static func_name      _getfuncname(QWORD dwFunc);
        private:
            static bool           m_bInitialized;
            func_name_list   m_lstFunc;
        };
    }
}


