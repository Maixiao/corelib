#pragma once
#ifdef CPPCORELIB_EXPORTS
#define CPPCORELIB_API __declspec(dllexport)
#else
#define CPPCORELIB_API __declspec(dllimport)
#endif