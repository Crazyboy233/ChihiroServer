#ifndef LOGGER_H
#define LOGGER_H

#include "LogLevel.h"
#include "LogAppender.h"
#include "LogEvent.h"
#include "LogFormatter.h"
#include <list>

// 添加LogFormatter的前置声明
namespace chihiro {
    
class LogFormatter;

// 日志器
class Logger {
public:
    using ptr = std::shared_ptr<Logger>;

    Logger(const std::string & name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

    LogLevel::Level setLevel(LogLevel::Level level);
    LogLevel::Level getLevel() const;

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

private:
    std::string m_name;                         // 日志名称
    LogLevel::Level m_level;                    // 日志级别
    std::list<LogAppender::ptr> m_appenders;    // 输出地集合
};

} // namespace chihiro

#endif