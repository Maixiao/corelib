#pragma once
#include "exp.h"
#include <list>
#include <memory>
#include <string>

namespace cpp {
    namespace corelib {
        class CPPCORELIB_API CallStack
        {
        public:
            typedef std::string             func_name;
            typedef std::list< func_name >                 func_name_list;
            typedef func_name_list::const_iterator         const_iterator;
            typedef std::shared_ptr<CallStack>        callstack_ptr;
            friend class CallStackImp;
        public:
            CallStack();
            ~CallStack();
        public:
            const_iterator begin() const;
            const_iterator end() const;
        public:
            static callstack_ptr generate(const void* pContext = NULL);
        private:
            std::shared_ptr<CallStackImp> m_spImp;
        };

    }
}

