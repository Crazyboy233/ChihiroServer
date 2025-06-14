#include "LogAppender.h"
#include <iostream>

namespace chihiro {

LogAppender::~LogAppender() {

}

void LogAppender::setFormatter(LogFormatter::ptr format) {
    m_formatter = format;
}

LogFormatter::ptr LogAppender::getFormatter() const {
    return nullptr;
}

/* ===============================输出到控制台===============================*/

StdoutLogAppender::StdoutLogAppender() {
    // 创建输出格式
    auto patternFormatter = std::make_shared<PatternFormatter>("%d [%p] %m%n");
    this->setFormatter(patternFormatter);
}

void StdoutLogAppender::append(LogEvent::ptr event) {
    if(m_formatter == nullptr) {
        throw std::runtime_error("No formatter set for ConsoleAppender");
    }
    
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << m_formatter->format(event);
}

/* ===============================输出到文件===============================*/

// FileLogAppender::FileLogAppender(const std::string &filename) 
//     :m_filename(filename)   {
// }

// void FileLogAppender::append(LogEvent::ptr event) {
//     m_filestream << m_formatter->format(event);

// }

// bool FileLogAppender::reopen() {
//     if(m_filestream) {
//         m_filestream.close();
//     }
//     m_filestream.open(m_filename);

//     // 文件打开成功返回True
//     return !!m_filestream;
// }

}