#include "log.h"
#include <iostream>

namespace chihiro {

void LogAppender::setFormatter(LogFormatter::ptr format) {
    m_formatter = format;
}

LogFormatter::ptr LogAppender::getFormatter() const {
    return m_formatter;
}

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


void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level){
        std::cout << m_formatter->format(event);
    }
}

FileLogAppender::FileLogAppender(const std::string &filename) 
    :m_filename(filename)   {
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level) {
        m_filestream << m_formatter->format(event);
    }
}

bool FileLogAppender::reopen() {
    if(m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);

    // 文件打开成功返回True
    return !!m_filestream;
}

}