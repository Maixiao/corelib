#include "stdafx.h"
#include "CallStack.h"
#include "CallStackImp.h"

namespace cpp {
    namespace corelib {
        CallStack::CallStack()
        {
            m_spImp = std::shared_ptr<CallStackImp>(new CallStackImp());
        }


        CallStack::~CallStack()
        {
        }

        CallStack::const_iterator CallStack::begin() const
        {
            return m_spImp->begin();
        }

        CallStack::const_iterator CallStack::end() const
        {
            return m_spImp->end();
        }

        CallStack::callstack_ptr CallStack::generate(const void* pContext /*= NULL*/)
        {
            return CallStackImp::generate(pContext);
        }
    }
}
