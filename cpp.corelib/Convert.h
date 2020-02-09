#pragma once
#include "exp.h"
#include <string>
#include "DateTime.h"
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

