#include "../include/LogAppender.h"
#include <iostream>

namespace chihiro {

void LogAppender::setFormatter(LogFormatter::ptr format) {
    m_formatter = format;
}

void StdoutLogAppender::log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level){
        std::cout << m_formatter->format(logger, level, event);
    }
}

FileLogAppender::FileLogAppender(const std::string &filename) 
    :m_filename(filename)   {
}

void FileLogAppender::log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) {
    if(level >= m_level) {
        m_filestream << m_formatter->format(logger, level, event);
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