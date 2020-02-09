#pragma once
#include "exp.h"
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
