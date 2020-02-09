#include "stdafx.h"
#include "Timespan.h"

namespace cpp
{
    namespace corelib
    {

        Timespan::Timespan() : _span(0)
        {
        }

        Timespan::Timespan(TimeDiff microseconds) :
            _span(microseconds)
        {

        }

        Timespan::Timespan(long seconds, long microseconds) :
            _span(TimeDiff(seconds)*SECONDS + microseconds)
        {

        }

        Timespan::Timespan(int days, int hours, int minutes, int seconds, int microSeconds) :
            _span(TimeDiff(microSeconds) + TimeDiff(seconds)*SECONDS + TimeDiff(minutes)*MINUTES + TimeDiff(hours)*HOURS + TimeDiff(days)*DAYS)
        {

        }

        Timespan::Timespan(const Timespan& timespan) :
            _span(timespan._span)
        {

        }

        Timespan::~Timespan()
        {
        }

        bool Timespan::operator>(const Timespan& ts) const
        {
            return _span > ts._span;
        }

        inline bool Timespan::operator >= (const Timespan& ts) const
        {
            return _span >= ts._span;
        }


        inline bool Timespan::operator <  (const Timespan& ts) const
        {
            return _span < ts._span;
        }


        inline bool Timespan::operator <= (const Timespan& ts) const
        {
            return _span <= ts._span;
        }


        inline bool Timespan::operator == (TimeDiff microSeconds) const
        {
            return _span == microSeconds;
        }


        inline bool Timespan::operator != (TimeDiff microSeconds) const
        {
            return _span != microSeconds;
        }


        inline bool Timespan::operator >  (TimeDiff microSeconds) const
        {
            return _span > microSeconds;
        }


        inline bool Timespan::operator >= (TimeDiff microSeconds) const
        {
            return _span >= microSeconds;
        }


        inline bool Timespan::operator <  (TimeDiff microSeconds) const
        {
            return _span < microSeconds;
        }


        inline bool Timespan::operator <= (TimeDiff microSeconds) const
        {
            return _span <= microSeconds;
        }

        inline bool Timespan::operator!=(const Timespan& ts) const
        {
            return _span != ts._span;
        }

        inline bool Timespan::operator==(const Timespan& ts) const
        {
            return _span == ts._span;
        }

        Timespan& Timespan::operator=(TimeDiff microseconds)
        {
            _span = microseconds;
            return *this;
        }

        Timespan& Timespan::operator=(const Timespan& timespan)
        {
            _span = timespan._span;
            return *this;
        }

        Timespan Timespan::operator + (const Timespan& d) const
        {
            return Timespan(_span + d._span);
        }


        Timespan Timespan::operator - (const Timespan& d) const
        {
            return Timespan(_span - d._span);
        }


        Timespan& Timespan::operator += (const Timespan& d)
        {
            _span += d._span;
            return *this;
        }


        Timespan& Timespan::operator -= (const Timespan& d)
        {
            _span -= d._span;
            return *this;
        }


        Timespan Timespan::operator + (TimeDiff microSeconds) const
        {
            return Timespan(_span + microSeconds);
        }


        Timespan Timespan::operator - (TimeDiff microSeconds) const
        {
            return Timespan(_span - microSeconds);
        }


        Timespan& Timespan::operator += (TimeDiff microSeconds)
        {
            _span += microSeconds;
            return *this;
        }


        Timespan& Timespan::operator -= (TimeDiff microSeconds)
        {
            _span -= microSeconds;
            return *this;
        }

        //
        // inlines
        //
        inline int Timespan::days() const
        {
            return int(_span / DAYS);
        }


        inline int Timespan::hours() const
        {
            return int((_span / HOURS) % 24);
        }


        inline int Timespan::totalHours() const
        {
            return int(_span / HOURS);
        }


        inline int Timespan::minutes() const
        {
            return int((_span / MINUTES) % 60);
        }


        inline int Timespan::totalMinutes() const
        {
            return int(_span / MINUTES);
        }


        inline int Timespan::seconds() const
        {
            return int((_span / SECONDS) % 60);
        }


        inline int Timespan::totalSeconds() const
        {
            return int(_span / SECONDS);
        }


        inline int Timespan::milliseconds() const
        {
            return int((_span / MILLISECONDS) % 1000);
        }


        inline Timespan::TimeDiff Timespan::totalMilliseconds() const
        {
            return _span / MILLISECONDS;
        }


        inline int Timespan::microseconds() const
        {
            return int(_span % 1000);
        }


        inline int Timespan::useconds() const
        {
            return int(_span % 1000000);
        }


        inline Timespan::TimeDiff Timespan::totalMicroseconds() const
        {
            return _span;
        }


        const Timespan::TimeDiff Timespan::MILLISECONDS = 1000;
        const Timespan::TimeDiff Timespan::SECONDS = 1000 * Timespan::MILLISECONDS;
        const Timespan::TimeDiff Timespan::MINUTES = 60 * Timespan::SECONDS;
        const Timespan::TimeDiff Timespan::HOURS = 60 * Timespan::MINUTES;
        const Timespan::TimeDiff Timespan::DAYS = 24 * Timespan::HOURS;


    }
}
