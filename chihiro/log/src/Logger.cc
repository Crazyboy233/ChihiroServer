#include "../include/Logger.h"

namespace chihiro {

Logger::Logger(const std::string & name) 
    :m_name(name),
    m_level(LogLevel::DEBUG),    // 默认为 DEBUG 级别
    m_parent(nullptr)
{
    // 创建输出目的地（控制台），添加到输出地集合
    auto coutAppender = std::make_shared<StdoutLogAppender>();
    m_appenders.push_back(coutAppender);
}

void Logger::log(LogLevel level, const std::string& msg) {
    // 检查日志级别，如果低于设置级别，则忽略
    if(level < m_level) {
        return;
    }

    // 否则创建日志事件
    auto event = std::make_shared<LogEvent>(level, "filename", __LINE__, 0, 0, 0, 0, msg);
    event->setLoggerName(m_name);

    std::lock_guard<std::mutex> lock(m_mutex);

    // 将日志发给 Appender
    for(auto appender : m_appenders) {
        appender->append(event);
    }

    // 如果有父 Logger 并且开启了向上传递，则将日志也发送给父 Logger
    if(m_parent != nullptr) {
        m_parent->log(m_level, msg);
    }
}

void Logger::debug(const std::string& msg) {
    log(LogLevel::DEBUG, msg);
}

void Logger::info(const std::string& msg) {
    log(LogLevel::INFO, msg);
}

void Logger::warn(const std::string& msg) {
    log(LogLevel::WARN, msg);
}

void Logger::error(const std::string& msg) {
    log(LogLevel::ERROR, msg);
}

void Logger::fatal(const std::string& msg) {
    log(LogLevel::FATAL, msg);
}

void Logger::addAppender(LogAppender::ptr appender) {
    std::lock_guard<std::mutex> lock(m_mutex);  // 加锁
    m_appenders.push_back(appender);    
}

void Logger::delAppender(LogAppender::ptr appender) {
    for(auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}

void Logger::setLevel(LogLevel level) {
    m_level = level;
}

LogLevel Logger::getLevel() const {
    return m_level;
}

// 设置父 Logger
void Logger::setParent(Logger::ptr parent) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_parent = parent;
}

Logger::ptr Logger::getParent() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_parent;
}

} // namespace chihiro