#include <iostream>
#include <sstream>
#include "cpp.corelib.h"
#pragma comment( lib, "cpp.corelib.lib" )
using namespace std;
using namespace cpp::corelib;


int main() {
    SehExceptionChecker::init();
    throw WindowsException();
    return 0;
}