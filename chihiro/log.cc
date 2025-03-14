#include "log.h"

namespace chihiro {

Logger::Logger(const std::string & name) 
    :m_name(name)
{

}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level > m_level) {
        for(auto it : m_appenders) {
            it->log(level, event);
        }
    }
}

void Logger::addAppender(LogAppender::ptr appender) {
    m_appenders.push_back(appender);    // 暂时不考虑线程安全问题
}

void Logger::delAppender(LogAppender::ptr appender) {
    for(auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if(*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}

LogLevel::Level Logger::setLevel(LogLevel::Level level) {
    m_level = level;
}

LogLevel::Level Logger::getLevel() const {
    return m_level;
}

void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::Level::DEBUG, event);
}

void Logger::info(LogEvent::ptr event) {
    log(LogLevel::Level::INFO, event);
}

void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::Level::WARN, event);
}

void Logger::error(LogEvent::ptr event) {
    log(LogLevel::Level::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event) {
    log(LogLevel::Level::FATAL, event);
}

}