#ifndef LOGGER_H
#define LOGGER_H

#include "LogLevel.h"
#include "LogAppender.h"
#include "LogEvent.h"
#include "LogFormatter.h"
#include <list>
 
#define LOG_DEBUG(logger, msg) (logger)->log(chihiro::LogLevel::DEBUG, msg, __FILE__, __LINE__)
#define LOG_INFO(logger, msg) (logger)->log(chihiro::LogLevel::INFO, msg, __FILE__, __LINE__)
#define LOG_WARN(logger, msg) (logger)->log(chihiro::LogLevel::WARN, msg, __FILE__, __LINE__)
#define LOG_ERROR(logger, msg) (logger)->log(chihiro::LogLevel::ERROR, msg, __FILE__, __LINE__)
#define LOG_FATAL(logger, msg) (logger)->log(chihiro::LogLevel::FATAL, msg, __FILE__, __LINE__)

namespace chihiro {
    
class LogFormatter;

// 日志器
class Logger {
public:
    using ptr = std::shared_ptr<Logger>;

    explicit Logger(const std::string & name = "root");

    // 日志记录接口
    void log(LogLevel level, const std::string& msg, const std::string& filename, const int lineNum);
    // void debug(const std::string& msg);
    // void info(const std::string& msg);
    // void warn(const std::string& msg);
    // void error(const std::string& msg);
    // void fatal(const std::string& msg);

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