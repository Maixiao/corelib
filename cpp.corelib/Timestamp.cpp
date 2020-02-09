#include "stdafx.h"
#include "Timestamp.h"
#include "Timespan.h"
#include <algorithm>
#undef min
#undef max
#include <limits>
namespace cpp {
    namespace corelib {
        const Timestamp::TimeVal Timestamp::TIMEVAL_MIN = std::numeric_limits<Timestamp::TimeVal>::min();
        const Timestamp::TimeVal Timestamp::TIMEVAL_MAX = std::numeric_limits<Timestamp::TimeVal>::max();

        Timestamp::Timestamp()
        {
            update();
        }


        Timestamp::Timestamp(TimeVal tv)
        {
            _ts = tv;
        }


        Timestamp::Timestamp(const Timestamp& other)
        {
            _ts = other._ts;
        }


        Timestamp::~Timestamp()
        {
        }

        Timestamp& Timestamp::operator = (const Timestamp& other)
        {
            _ts = other._ts;
            return *this;
        }


        Timestamp& Timestamp::operator = (TimeVal tv)
        {
            _ts = tv;
            return *this;
        }

        Timestamp Timestamp::fromEpochTime(std::time_t t)
        {
            return Timestamp(TimeVal(t)*resolution());
        }

        Timestamp Timestamp::fromUtcTime(UtcTimeVal val)
        {
            val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
            val /= 10;
            return Timestamp(val);
        }

        void Timestamp::update()
        {
            FILETIME ft;
            GetSystemTimeAsFileTime(&ft);
            ULARGE_INTEGER epoch;
            epoch.LowPart = 0xD53E8000;
            epoch.HighPart = 0x019DB1DE;

            ULARGE_INTEGER ts;
            ts.LowPart = ft.dwLowDateTime;
            ts.HighPart = ft.dwHighDateTime;
            ts.QuadPart -= epoch.QuadPart;
            _ts = ts.QuadPart / 10;
        }

        Timestamp  Timestamp::operator +  (const Timespan& span) const
        {
            return *this + span.totalMicroseconds();
        }


        Timestamp  Timestamp::operator -  (const Timespan& span) const
        {
            return *this - span.totalMicroseconds();
        }


        Timestamp& Timestamp::operator += (const Timespan& span)
        {
            return *this += span.totalMicroseconds();
        }


        Timestamp& Timestamp::operator -= (const Timespan& span)
        {
            return *this -= span.totalMicroseconds();
        }

        inline bool Timestamp::operator == (const Timestamp& ts) const
        {
            return _ts == ts._ts;
        }


        inline bool Timestamp::operator != (const Timestamp& ts) const
        {
            return _ts != ts._ts;
        }


        inline bool Timestamp::operator >  (const Timestamp& ts) const
        {
            return _ts > ts._ts;
        }


        inline bool Timestamp::operator >= (const Timestamp& ts) const
        {
            return _ts >= ts._ts;
        }


        inline bool Timestamp::operator <  (const Timestamp& ts) const
        {
            return _ts < ts._ts;
        }


        inline bool Timestamp::operator <= (const Timestamp& ts) const
        {
            return _ts <= ts._ts;
        }


        inline Timestamp Timestamp::operator + (Timestamp::TimeDiff d) const
        {
            return Timestamp(_ts + d);
        }


        inline Timestamp Timestamp::operator - (Timestamp::TimeDiff d) const
        {
            return Timestamp(_ts - d);
        }


        inline Timestamp::TimeDiff Timestamp::operator - (const Timestamp& ts) const
        {
            return _ts - ts._ts;
        }


        inline Timestamp& Timestamp::operator += (Timestamp::TimeDiff d)
        {
            _ts += d;
            return *this;
        }


        inline Timestamp& Timestamp::operator -= (Timestamp::TimeDiff d)
        {
            _ts -= d;
            return *this;
        }


        inline std::time_t Timestamp::epochTime() const
        {
            return std::time_t(_ts / resolution());
        }


        Timestamp::UtcTimeVal Timestamp::utcTime() const
        {
            return _ts * 10 + (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
        }

        inline Timestamp::TimeDiff Timestamp::elapsed() const
        {
            Timestamp now;
            return now - *this;
        }


        inline bool Timestamp::isElapsed(Timestamp::TimeDiff interval) const
        {
            Timestamp now;
            Timestamp::TimeDiff diff = now - *this;
            return diff >= interval;
        }


        inline Timestamp::TimeDiff Timestamp::resolution()
        {
            return 1000000;
        }


        inline Timestamp::TimeVal Timestamp::raw() const
        {
            return _ts;
        }
    }
}
