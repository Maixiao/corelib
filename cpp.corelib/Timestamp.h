#pragma once
#include "exp.h"
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


