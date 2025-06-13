#include "LogEvent.h"
namespace chihiro {

// LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel level, 
//                 const char *file, int32_t line, 
//                 uint32_t elapse, uint32_t threadId, 
//                 uint32_t fiberId, uint64_t time, 
//                 const std::string &content) 
//     :m_file(file),
//     m_line(line),
//     m_elapse(elapse),
//     m_threadId(threadId),
//     m_fiberID(fiberId),
//     m_time(time),
//     m_content(content),
//     m_logger(logger),
//     m_level(level)
// {
    
// }

LogEvent::LogEvent(LogLevel level, 
                const std::string fileName, int32_t line, 
                uint32_t elapse, uint32_t threadId, 
                uint32_t fiberId, uint64_t time, 
                const std::string &content) 
    :m_file_name(fileName),
    m_line(line),
    m_elapse(elapse),
    m_threadId(threadId),
    m_fiberID(fiberId),
    m_time(time),
    m_content(content),
    // m_logger(logger),
    m_level(level)
{

}

const std::string LogEvent::getFileName() const {
    return m_file_name;
}

int32_t LogEvent::getLine() const {
    return m_line;
}

uint32_t LogEvent::getElapse() const {
    return m_elapse;
}

uint32_t LogEvent::getThreadId() const {
    return m_threadId;
}

uint32_t LogEvent::getFiberId() const {
    return m_fiberID;
}

uint64_t LogEvent::getTime() const {
    return m_time;
}

std::string LogEvent::getContent() const {
    return m_content;
}

LogLevel LogEvent::getLevel() const {
    return m_level;
}

std::string LogEvent::getLevelStr() const {
    switch (m_level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string LogEvent::getMessage() const {
    return m_content;
}



void LogEvent::setLoggerName(const std::string& logname) {
    m_name = logname;
}

} // namespace chihiro