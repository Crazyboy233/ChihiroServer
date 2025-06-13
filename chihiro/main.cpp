#include "Logger.h"
#include <iostream>

using namespace chihiro;

int main() {
    Logger log;
    log.log(LogLevel::DEBUG, "this is a log");
    return 0;
}