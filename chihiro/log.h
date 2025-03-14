#ifndef __CHIHIRO_LOG_H__
#define __CHIHIRO_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
namespace chihiro{

// 日志事件
class LogEvent{
public:
    using ptr = std::shared_ptr<LogEvent>;

    LogEvent();
private:   
    const char * m_file = nullptr;  // 文件名
    int32_t m_line = 0;             // 行号
    uint32_t m_elapse = 0;          // 程序启动到现在的毫秒数
    uint32_t m_threadId = 0;        // 线程ID
    uint32_t m_fiberID = 0;         // 协程ID
    uint64_t m_time = 0;            // 时间
    std::string m_content;          // 消息
};

// 日志级别
// TODO:可以考虑 enum class 
class LogLevel{
public:
    
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

// 日志格式器
class LogFormatter{
public:
    using ptr = std::shared_ptr<LogFormatter>;

    std::string format(LogEvent::ptr event);
private:
};

// 日志输出地
class LogAppender{
public:
    using ptr = std::shared_ptr<LogAppender>;

    virtual ~LogAppender();  // 可能有很多输出地，所以设置为虚析构函数
    
    void log(LogLevel::Level level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;
};



// 日志器
class Logger{
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
    std::list<LogAppender::ptr> m_appenders;    // Appender集合
};

// 输出到控制台
class StdoutLogAppender : public LogAppender {

};

// 输出到文件
class FileLogAppender : public LogAppender {

};
}

#endif __CHIHIRO_LOG_H__