#include "LogEvent.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace chihiro {

LogEvent::LogEvent(LogLevel level, 
                const std::string fileName, int32_t line, 
                uint32_t elapse, uint32_t threadId, 
                uint32_t fiberId, std::string time, 
                const std::string &content) 
    :m_file_name(fileName),
    m_line(line),
    m_elapse(elapse),
    m_threadId(threadId),
    m_fiberID(fiberId),
    m_time(time),
    m_content(content),
    m_level(level)
{
    this->init();
}

void LogEvent::init() {
    // 设置时间
    auto now = std::chrono::system_clock::now();    // 获取当前时间
    auto now_c = std::chrono::system_clock::to_time_t(now); // 将当前时间转化为time_t类型
    auto now_tm = *std::localtime(&now_c);   // 将time_t转化为本地时间结构

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");    // 使用put_time按"年-月-日 时:分:秒"格式输出
    m_time = oss.str();

    //

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

std::string LogEvent::getTime() const {
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

void LogEvent::setTime(const std::string& time) {
    m_time = time;
}

void LogEvent::setLoggerName(const std::string& logname) {
    m_name = logname;
}

} // namespace chihiro