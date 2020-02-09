#pragma once
#include "exp.h"
#include "Timestamp.h"

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


