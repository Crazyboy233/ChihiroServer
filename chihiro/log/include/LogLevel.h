#ifndef LOGLEVEL_H
#define LOGLEVEL_H

namespace chihiro {

// 日志级别
// TODO:可以考虑 enum class 
enum class LogLevel {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
};

} // namespace chihiro

#endif