#include "stdafx.h"
#include "DateTime.h"
#include "Timestamp.h"
#include "Timespan.h"
#include "Exception.h"

namespace cpp {
    namespace corelib {
        DateTime::DateTime()
        {
            Timestamp now;
            _utcTime = now.utcTime();
            computeGregorian(julianDay());
            computeDaytime();
        }

        DateTime::DateTime(const Timestamp& timestamp) :
            _utcTime(timestamp.utcTime())
        {
            computeGregorian(julianDay());
            computeDaytime();
        }

        DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond) :
            _year(year),
            _month(month),
            _day(day),
            _hour(hour),
            _minute(minute),
            _second(second),
            _millisecond(millisecond),
            _microsecond(microsecond)
        {
            if ((year >= 0 && year <= 9999
                || month >= 1 && month <= 12
                || day >= 1 && day <= daysOfMonth(year, month)
                || hour >= 0 && hour <= 23
                || minute >= 0 && minute <= 59
                || second >= 0 && second <= 60
                || millisecond >= 0 && millisecond <= 999
                || microsecond >= 0 && microsecond <= 999) == false) {
                throw Exception("Invalid Parameter Exception");
            }
            _utcTime = toUtcTime(toJulianDay(year, month, day)) + 10 * (hour*Timespan::HOURS + minute*Timespan::MINUTES + second*Timespan::SECONDS + millisecond*Timespan::MILLISECONDS + microsecond);
        }

        DateTime::DateTime(const DateTime& dateTime) :
            _utcTime(dateTime._utcTime),
            _year(dateTime._year),
            _month(dateTime._month),
            _day(dateTime._day),
            _hour(dateTime._hour),
            _minute(dateTime._minute),
            _second(dateTime._second),
            _millisecond(dateTime._millisecond),
            _microsecond(dateTime._microsecond)
        {
        }


        DateTime::DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff)
        {
            computeGregorian(julianDay());
            computeDaytime();
        }

        DateTime::~DateTime()
        {
        }

        DateTime& DateTime::operator = (const DateTime& dateTime)
        {
            if (&dateTime != this)
            {
                _utcTime = dateTime._utcTime;
                _year = dateTime._year;
                _month = dateTime._month;
                _day = dateTime._day;
                _hour = dateTime._hour;
                _minute = dateTime._minute;
                _second = dateTime._second;
                _millisecond = dateTime._millisecond;
                _microsecond = dateTime._microsecond;
            }
            return *this;
        }


        DateTime& DateTime::operator = (const Timestamp& timestamp)
        {
            _utcTime = timestamp.utcTime();
            computeGregorian(julianDay());
            computeDaytime();
            return *this;
        }

        int DateTime::dayOfWeek() const
        {
            return int((std::floor(julianDay() + 1.5))) % 7;
        }


        int DateTime::dayOfYear() const
        {
            int doy = 0;
            for (int month = 1; month < _month; ++month)
                doy += daysOfMonth(_year, month);
            doy += _day;
            return doy;
        }


        int DateTime::daysOfMonth(int year, int month)
        {
            if ((month >= 1 && month <= 12) == false) {
                throw Exception("Invalid Parameter Exception");
            }

            static int daysOfMonthTable[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            if (month == 2 && isLeapYear(year))
                return 29;
            else
                return daysOfMonthTable[month];
        }


        bool DateTime::isValid(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
        {
            return
                (year >= 0 && year <= 9999) &&
                (month >= 1 && month <= 12) &&
                (day >= 1 && day <= daysOfMonth(year, month)) &&
                (hour >= 0 && hour <= 23) &&
                (minute >= 0 && minute <= 59) &&
                (second >= 0 && second <= 60) &&
                (millisecond >= 0 && millisecond <= 999) &&
                (microsecond >= 0 && microsecond <= 999);
        }


        int DateTime::week(int firstDayOfWeek) const
        {
            if ((firstDayOfWeek >= 0 && firstDayOfWeek <= 6) == false) {
                throw Exception("Invalid Parameter Exception");
            }

            /// find the first firstDayOfWeek.
            int baseDay = 1;
            while (DateTime(_year, 1, baseDay).dayOfWeek() != firstDayOfWeek) ++baseDay;

            int doy = dayOfYear();
            int offs = baseDay <= 4 ? 0 : 1;
            if (doy < baseDay)
                return offs;
            else
                return (doy - baseDay) / 7 + 1 + offs;
        }


        double DateTime::julianDay() const
        {
            return toJulianDay(_utcTime);
        }

        DateTime DateTime::operator + (const Timespan& span) const
        {
            return DateTime(_utcTime, span.totalMicroseconds());
        }


        DateTime DateTime::operator - (const Timespan& span) const
        {
            return DateTime(_utcTime, -span.totalMicroseconds());
        }


        Timespan DateTime::operator - (const DateTime& dateTime) const
        {
            return Timespan((_utcTime - dateTime._utcTime) / 10);
        }


        DateTime& DateTime::operator += (const Timespan& span)
        {
            _utcTime += span.totalMicroseconds() * 10;
            computeGregorian(julianDay());
            computeDaytime();
            return *this;
        }


        DateTime& DateTime::operator -= (const Timespan& span)
        {
            _utcTime -= span.totalMicroseconds() * 10;
            computeGregorian(julianDay());
            computeDaytime();
            return *this;
        }

        double DateTime::toJulianDay(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
        {
            // lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
            static int lookup[] = { -91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337 };

            // day to double
            double dday = double(day) + ((double((hour * 60 + minute) * 60 + second) * 1000 + millisecond) * 1000 + microsecond) / 86400000000.0;
            if (month < 3)
            {
                month += 12;
                --year;
            }
            double dyear = double(year);
            return dday + lookup[month] + 365 * year + std::floor(dyear / 4) - std::floor(dyear / 100) + std::floor(dyear / 400) + 1721118.5;
        }


        double DateTime::toJulianDay(Timestamp::UtcTimeVal utcTime)
        {
            double utcDays = double(utcTime) / 864000000000.0;
            return utcDays + 2299160.5; // first day of Gregorian reform (Oct 15 1582)
        }

        Timestamp::UtcTimeVal DateTime::toUtcTime(double julianDay)
        {
            return Timestamp::UtcTimeVal((julianDay - 2299160.5)*864000000000.0);
        }

        void DateTime::checkLimit(short& lower, short& higher, short limit)
        {
            if (lower >= limit)
            {
                higher += short(lower / limit);
                lower = short(lower % limit);
            }
        }


        void DateTime::normalize()
        {
            checkLimit(_microsecond, _millisecond, 1000);
            checkLimit(_millisecond, _second, 1000);
            checkLimit(_second, _minute, 60);
            checkLimit(_minute, _hour, 60);
            checkLimit(_hour, _day, 24);

            if (_day > daysOfMonth(_year, _month))
            {
                _day -= daysOfMonth(_year, _month);
                if (++_month > 12)
                {
                    ++_year;
                    _month -= 12;
                }
            }
        }


        void DateTime::computeGregorian(double julianDay)
        {
            double z = std::floor(julianDay - 1721118.5);
            double r = julianDay - 1721118.5 - z;
            double g = z - 0.25;
            double a = std::floor(g / 36524.25);
            double b = a - std::floor(a / 4);
            _year = short(std::floor((b + g) / 365.25));
            double c = b + z - std::floor(365.25*_year);
            _month = short(std::floor((5 * c + 456) / 153));
            double dday = c - std::floor((153.0*_month - 457) / 5) + r;
            _day = short(dday);
            if (_month > 12)
            {
                ++_year;
                _month -= 12;
            }
            r *= 24;
            _hour = short(std::floor(r));
            r -= std::floor(r);
            r *= 60;
            _minute = short(std::floor(r));
            r -= std::floor(r);
            r *= 60;
            _second = short(std::floor(r));
            r -= std::floor(r);
            r *= 1000;
            _millisecond = short(std::floor(r));
            r -= std::floor(r);
            r *= 1000;
            _microsecond = short(r + 0.5);

            normalize();

            if ((_month >= 1 && _month <= 12
                || _day >= 1 && _day <= daysOfMonth(_year, _month)
                || _hour >= 0 && _hour <= 23
                || _minute >= 0 && _minute <= 59
                || _second >= 0 && _second <= 59
                || _millisecond >= 0 && _millisecond <= 999
                || _microsecond >= 0 && _microsecond <= 999) == false) {
                throw Exception("Invalid Parameter Exception");
            }
        }


        void DateTime::computeDaytime()
        {
            Timespan span(_utcTime / 10);
            int hour = span.hours();
            // Due to double rounding issues, the previous call to computeGregorian()
            // may have crossed into the next or previous day. We need to correct that.
            if (hour == 23 && _hour == 0)
            {
                _day--;
                if (_day == 0)
                {
                    _month--;
                    if (_month == 0)
                    {
                        _month = 12;
                        _year--;
                    }
                    _day = daysOfMonth(_year, _month);
                }
            }
            else if (hour == 0 && _hour == 23)
            {
                _day++;
                if (_day > daysOfMonth(_year, _month))
                {
                    _month++;
                    if (_month > 12)
                    {
                        _month = 1;
                        _year++;
                    }
                    _day = 1;
                }
            }
            _hour = hour;
            _minute = span.minutes();
            _second = span.seconds();
            _millisecond = span.milliseconds();
            _microsecond = span.microseconds();
        }





        inline Timestamp DateTime::timestamp() const
        {
            return Timestamp::fromUtcTime(_utcTime);
        }


        inline int DateTime::year() const
        {
            return _year;
        }


        inline int DateTime::month() const
        {
            return _month;
        }


        inline int DateTime::day() const
        {
            return _day;
        }


        inline int DateTime::hour() const
        {
            return _hour;
        }


        inline int DateTime::hourAMPM() const
        {
            if (_hour < 1)
                return 12;
            else if (_hour > 12)
                return _hour - 12;
            else
                return _hour;
        }


        inline bool DateTime::isAM() const
        {
            return _hour < 12;
        }


        inline bool DateTime::isPM() const
        {
            return _hour >= 12;
        }


        inline int DateTime::minute() const
        {
            return _minute;
        }


        inline int DateTime::second() const
        {
            return _second;
        }


        inline int DateTime::millisecond() const
        {
            return _millisecond;
        }


        inline int DateTime::microsecond() const
        {
            return _microsecond;
        }


        inline bool DateTime::operator == (const DateTime& dateTime) const
        {
            return _utcTime == dateTime._utcTime;
        }


        inline bool DateTime::operator != (const DateTime& dateTime) const
        {
            return _utcTime != dateTime._utcTime;
        }


        inline bool DateTime::operator <  (const DateTime& dateTime) const
        {
            return _utcTime < dateTime._utcTime;
        }


        inline bool DateTime::operator <= (const DateTime& dateTime) const
        {
            return _utcTime <= dateTime._utcTime;
        }


        inline bool DateTime::operator >  (const DateTime& dateTime) const
        {
            return _utcTime > dateTime._utcTime;
        }


        inline bool DateTime::operator >= (const DateTime& dateTime) const
        {
            return _utcTime >= dateTime._utcTime;
        }


        inline bool DateTime::isLeapYear(int year)
        {
            return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
        }


    }
}
