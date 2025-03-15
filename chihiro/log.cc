#include "log.h"
#include <iostream>

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


std::string LogFormatter::format(LogEvent::ptr event)
{
    std::stringstream ss;
    // ss <<

    std::string result = ss.str();
    return result;
}
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