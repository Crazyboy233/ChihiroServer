#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <string>

namespace chihiro {

// 日志级别
// TODO:可以考虑 enum class 
class LogLevel {
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    static std::string toString(LogLevel::Level level);
};

} // namespace chihiro

#endif