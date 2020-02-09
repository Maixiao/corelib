// cpp.corelib.cpp : 定义 DLL 应用程序的导出函数。
//

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>



// TODO:  在此处引用程序需要的其他头文件

#pragma once
#ifdef CPPCORELIB_EXPORTS
#define CPPCORELIB_API __declspec(dllexport)
#else
#define CPPCORELIB_API __declspec(dllimport)
#endif
#pragma once

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


#pragma once


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



#pragma once

#include <string>
#include <stdexcept>

using namespace std;
namespace cpp
{
    namespace corelib {
        class CPPCORELIB_API Exception
            : public std::exception
        {
        public:
            Exception(string name);
            Exception(_EXCEPTION_POINTERS* exp, string name = "Exception");
            void AppendMessage(string msg);
            ~Exception();
            virtual char const* what() const;
        protected:
            string name;
            string msgStr;
            CallStack::callstack_ptr pCall = nullptr;
            string traceStack() const;
        };
    }
}


#pragma once


namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API AccessViolationException
            : public Exception
        {
        public:
            AccessViolationException();
            AccessViolationException(_EXCEPTION_POINTERS* exp);
            ~AccessViolationException();
        };
    }
}

#pragma once


namespace cpp
{
    namespace corelib {
        class CPPCORELIB_API DivideByZeroException
            : public Exception
        {
        public:
            DivideByZeroException();
            DivideByZeroException(_EXCEPTION_POINTERS* exp);
            ~DivideByZeroException();
        };

    }
}


#pragma once


namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API InvalidHandleException
            : public Exception
        {
        public:
            InvalidHandleException();
            InvalidHandleException(_EXCEPTION_POINTERS* exp);
            ~InvalidHandleException();
        };
    }
}


#pragma once


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


#pragma once

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



#pragma once

namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API Timespan
        {
        public:
            typedef signed long long TimeDiff;
        public:
            Timespan();
            Timespan(TimeDiff microseconds);
            Timespan(long seconds, long microseconds);
            Timespan(int days, int hours, int minutes, int seconds, int microSeconds);
            Timespan(const Timespan& timespan);
            ~Timespan();
            Timespan& operator = (const Timespan& timespan);
            Timespan& operator = (TimeDiff microseconds);

            bool operator == (const Timespan& ts) const;
            bool operator != (const Timespan& ts) const;
            bool operator >  (const Timespan& ts) const;
            bool operator >= (const Timespan& ts) const;
            bool operator <  (const Timespan& ts) const;
            bool operator <= (const Timespan& ts) const;

            bool operator == (TimeDiff microSeconds) const;
            bool operator != (TimeDiff microSeconds) const;
            bool operator >  (TimeDiff microSeconds) const;
            bool operator >= (TimeDiff microSeconds) const;
            bool operator <  (TimeDiff microSeconds) const;
            bool operator <= (TimeDiff microSeconds) const;

            Timespan operator + (const Timespan& d) const;
            Timespan operator - (const Timespan& d) const;
            Timespan& operator += (const Timespan& d);
            Timespan& operator -= (const Timespan& d);

            Timespan operator + (TimeDiff microSeconds) const;
            Timespan operator - (TimeDiff microSeconds) const;
            Timespan& operator += (TimeDiff microSeconds);
            Timespan& operator -= (TimeDiff microSeconds);

            int days() const;
            int hours() const;
            int totalHours() const;
            int minutes() const;
            int totalMinutes() const;
            int seconds() const;
            int totalSeconds() const;
            int milliseconds() const;
            TimeDiff totalMilliseconds() const;
            int microseconds() const;
            int useconds() const;
            TimeDiff totalMicroseconds() const;
            static const TimeDiff MILLISECONDS; /// The number of microseconds in a millisecond.
            static const TimeDiff SECONDS;      /// The number of microseconds in a second.
            static const TimeDiff MINUTES;      /// The number of microseconds in a minute.
            static const TimeDiff HOURS;        /// The number of microseconds in a hour.
            static const TimeDiff DAYS;         /// The number of microseconds in a day.
        private:
            TimeDiff _span;
        };

    }
}

#pragma once

#include <ctime>

namespace cpp {
    namespace corelib {
        class Timespan;
        class CPPCORELIB_API Timestamp
        {
        public:
            typedef signed long long TimeVal;
            typedef signed long long UtcTimeVal;
            typedef signed long long TimeDiff;
            static const TimeVal TIMEVAL_MIN; /// Minimum timestamp value.
            static const TimeVal TIMEVAL_MAX; /// Maximum timestamp value.
        public:
            Timestamp();
            Timestamp(TimeVal tv);
            Timestamp(const Timestamp& other);
            ~Timestamp();
            Timestamp& operator = (const Timestamp& other);
            Timestamp& operator = (TimeVal tv);
            void update();

            bool operator == (const Timestamp& ts) const;
            bool operator != (const Timestamp& ts) const;
            bool operator >  (const Timestamp& ts) const;
            bool operator >= (const Timestamp& ts) const;
            bool operator <  (const Timestamp& ts) const;
            bool operator <= (const Timestamp& ts) const;

            Timestamp  operator +  (TimeDiff d) const;
            Timestamp  operator +  (const Timespan& span) const;
            Timestamp  operator -  (TimeDiff d) const;
            Timestamp  operator -  (const Timespan& span) const;
            TimeDiff   operator -  (const Timestamp& ts) const;
            Timestamp& operator += (TimeDiff d);
            Timestamp& operator += (const Timespan& span);
            Timestamp& operator -= (TimeDiff d);
            Timestamp& operator -= (const Timespan& span);

            std::time_t epochTime() const;
            UtcTimeVal utcTime() const;
            TimeDiff elapsed() const;
            bool isElapsed(TimeDiff interval) const;
            TimeVal raw() const;
            static Timestamp fromEpochTime(std::time_t t);
            static Timestamp fromUtcTime(UtcTimeVal val);
            static TimeDiff resolution();
        private:
            TimeVal _ts;
        };
    }
}



#pragma once



namespace cpp {
    namespace corelib {
        class CPPCORELIB_API DateTime
        {
        public:
            enum Months
            {
                JANUARY = 1,
                FEBRUARY,
                MARCH,
                APRIL,
                MAY,
                JUNE,
                JULY,
                AUGUST,
                SEPTEMBER,
                OCTOBER,
                NOVEMBER,
                DECEMBER
            };
            enum DaysOfWeek
            {
                SUNDAY = 0,
                MONDAY,
                TUESDAY,
                WEDNESDAY,
                THURSDAY,
                FRIDAY,
                SATURDAY
            };

            DateTime();
            DateTime(const Timestamp&);
            DateTime(Timestamp::UtcTimeVal, Timestamp::TimeDiff);
            DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
            DateTime(const DateTime& dateTime);
            ~DateTime();

            DateTime& operator = (const DateTime& dateTime);
            DateTime& operator = (const Timestamp& timestamp);


            int year() const;
            int month() const;
            int week(int firstDayOfWeek) const;
            double julianDay() const;
            Timestamp timestamp() const;
            int day() const;
            int dayOfWeek() const;
            int dayOfYear() const;
            int hour() const;
            int hourAMPM() const;
            bool isAM() const;
            bool isPM() const;
            int minute() const;
            int second() const;
            int millisecond() const;
            int microsecond() const;

            bool operator == (const DateTime& dateTime) const;
            bool operator != (const DateTime& dateTime) const;
            bool operator <  (const DateTime& dateTime) const;
            bool operator <= (const DateTime& dateTime) const;
            bool operator >  (const DateTime& dateTime) const;
            bool operator >= (const DateTime& dateTime) const;

            DateTime  operator +  (const Timespan& span) const;
            DateTime  operator -  (const Timespan& span) const;
            Timespan  operator -  (const DateTime& dateTime) const;
            DateTime& operator += (const Timespan& span);
            DateTime& operator -= (const Timespan& span);

            static bool isLeapYear(int year);
            static int daysOfMonth(int year, int month);
            static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
        protected:
            static double toJulianDay(Timestamp::UtcTimeVal utcTime);
            static double toJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
            static Timestamp::UtcTimeVal toUtcTime(double julianDay);
            void computeGregorian(double julianDay);
            void computeDaytime();
        private:
            void checkLimit(short& lower, short& higher, short limit);
            void normalize();

            Timestamp::UtcTimeVal _utcTime;
            short  _year;
            short  _month;
            short  _day;
            short  _hour;
            short  _minute;
            short  _second;
            short  _millisecond;
            short  _microsecond;
        };
    }
}



#pragma once

#include <string>

using namespace std;
namespace cpp
{
    namespace corelib
    {
        class CPPCORELIB_API Convert
        {
        public:
            static string ToString(int value);
            static string ToString(char value);
            static string ToString(long value);
            static string ToString(float value);
            static string ToString(double value);
            static string ToString(DateTime value);
            static int ToInt(string value);
            static int ToDouble(string value);
            static DateTime ToDateTime(string value);
            static char ToChar(string value);
            static bool ToBoolean(string value);
            static string ToBase64String(char* inArray, int length);
            static char* FromBase64String(string s, int& length);
        };

    }
}


#pragma once

#include <string>
using namespace std;
namespace cpp 
{
    namespace corelib
    {
        class CPPCORELIB_API Encoding
        {
        public:
            class Unicode;
            class UTF8;
        public:
            virtual string GetString(char* bytes, int count) = 0;
            virtual char* GetBytes(string s, int& count) = 0;
        };


        class CPPCORELIB_API Unicode : public Encoding
        {
        public:
            virtual string GetString(char* bytes, int count) override;
            virtual char* GetBytes(string s, int& count) override;

        };

        class CPPCORELIB_API UTF8 : public Encoding
        {
        public:
            virtual string GetString(char* bytes, int count) override;
            virtual char* GetBytes(string s, int& count) override;
        };

    }
}




