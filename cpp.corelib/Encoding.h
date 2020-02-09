#pragma once
#include "exp.h"
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

