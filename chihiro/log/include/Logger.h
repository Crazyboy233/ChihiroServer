#ifndef LOGGER_H
#define LOGGER_H

#include "LogLevel.h"
#include "LogAppender.h"
#include "LogEvent.h"
#include "LogFormatter.h"
#include <list>
 
namespace chihiro {
    
class LogFormatter;

// 日志器
class Logger {
public:
    using ptr = std::shared_ptr<Logger>;

    explicit Logger(const std::string & name = "root");

    // 日志记录接口
    void log(LogLevel level, const std::string& msg);
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void fatal(const std::string& msg);

    // 配置方法
    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void setLevel(LogLevel level);
    LogLevel getLevel() const;
    const std::string& getName() const;

    // 设置父 Logger
    void setParent(Logger::ptr parent);
    Logger::ptr getParent() const;

private:
    std::string m_name;                         // 日志名称
    LogLevel m_level;                           // 日志级别
    std::vector<LogAppender::ptr> m_appenders;  // 输出地集合
    Logger::ptr m_parent;                       // 父 Logger（用于层级结构）
    mutable std::mutex m_mutex;                 // 线程安全锁
};

} // namespace chihiro

#endif