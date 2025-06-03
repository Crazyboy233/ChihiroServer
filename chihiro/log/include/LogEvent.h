#ifndef LOGGEREVENT_H
#define LOGGEREVENT_H

#include "Logger.h"
#include <memory>

namespace chihiro {

class Logger;

// 日志事件
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;

    // LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, 
    //         const char * file, int32_t line, 
    //         uint32_t elapse, uint32_t threadId, 
    //         uint32_t fiberId, uint64_t time,
    //         const std::string & content);

    LogEvent(LogLevel::Level level, 
            const char * file, int32_t line, 
            uint32_t elapse, uint32_t threadId, 
            uint32_t fiberId, uint64_t time,
            const std::string & content);

    // 获取日志信息
    const char * getFile() const;
    int32_t getLine() const;
    uint32_t getElapse() const;
    uint32_t getThreadId() const;
    uint32_t getFiberId() const;
    uint64_t getTime() const;
    std::string getContent() const;
    std::shared_ptr<Logger> getLogger() const;
    LogLevel::Level getLevel() const;
    std::string getLevelStr() const;

private:
    const char * m_file = nullptr;      // 文件名
    int32_t m_line = 0;                 // 文件行号
    uint32_t m_elapse = 0;              // 程序启动到现在的毫秒数
    uint32_t m_threadId = 0;            // 线程ID
    uint32_t m_fiberID = 0;             // 协程ID
    uint64_t m_time = 0;                // 时间
    std::string m_content;              // 消息
    // std::shared_ptr<Logger> m_logger;   // 日志器
    LogLevel::Level m_level;            // 日志级别
};

} // namespace chihiro

#endif