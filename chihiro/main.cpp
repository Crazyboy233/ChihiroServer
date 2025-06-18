#include "Logger.h"
#include <iostream>

using namespace chihiro;

int main() {
    Logger log;
    LOG_DEBUG(&log, "This is a log");
    return 0;
}