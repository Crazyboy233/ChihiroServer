#include "../include/LogEvent.h"
namespace chihiro {

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, 
                const char *file, int32_t line, 
                uint32_t elapse, uint32_t threadId, 
                uint32_t fiberId, uint64_t time, 
                const std::string &content) 
    :m_file(file),
    m_line(line),
    m_elapse(elapse),
    m_threadId(threadId),
    m_fiberID(fiberId),
    m_time(time),
    m_content(content),
    m_logger(logger),
    m_level(level)
{
    
}

const char *LogEvent::getFile() const {
    return m_file;
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
std::shared_ptr<Logger> LogEvent::getLogger() const {
    return m_logger;
}
LogLevel::Level LogEvent::getLevel() const {
    return m_level;
}
std::string LogEvent::getLevelStr() const {
    return LogLevel::toString(m_level);
}

} // namespace chihiro