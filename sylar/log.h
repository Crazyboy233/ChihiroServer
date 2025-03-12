#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
namespace sylar{

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
    
    void log(LogLevel level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;
};



// 日志器
class Logger{
public:
    using ptr = std::shared_ptr<Logger>;

    Logger(const std::string name = "root");

    void log(LogLevel level, LogEvent::ptr event);
private:
    std::string m_name;
    LogLevel::Level m_level;
    LogAppender::ptr m_event;
};

// 输出到控制台
class StdoutLogAppender : public LogAppender {

};

// 输出到文件
class FileLogAppender : public LogAppender {

};
}

#endif __SYLAR_LOG_H__