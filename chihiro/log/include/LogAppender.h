#ifndef __CHIHIRO_LOGAPPENDER_H__
#define __CHIHIRO_LOGAPPENDER_H__

#include "LogFormatter.h"
#include <mutex>
#include <sstream>
#include <fstream>

namespace chihiro {


// 日志输出地
class LogAppender {
public:
    using ptr = std::shared_ptr<LogAppender>;

    virtual ~LogAppender(); 
    
    virtual void append(LogEvent::ptr event) = 0;

    // 设置输出格式
    void setFormatter(LogFormatter::ptr format);

    // 获取输出格式
    LogFormatter::ptr getFormatter() const;

protected:
    LogLevel m_level;        // 日志级别
    LogFormatter::ptr m_formatter;  // 输出格式器
    std::mutex m_mutex;             // 用于线程安全
    
};

// 输出到控制台
class StdoutLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;

    StdoutLogAppender();
    void append(LogEvent::ptr event) override;
private:
};

// 输出到文件
// class FileLogAppender : public LogAppender {
// public:
//     using ptr = std::shared_ptr<FileLogAppender>;
//     FileLogAppender(const std::string & filename);

//     void append(LogEvent::ptr event) override;

//     /// @brief 重新打开文件
//     /// @return 成功返回True，失败返回False
//     bool reopen();
// private:
//     std::string m_filename;
//     std::ofstream m_filestream;
// };

} // namespace chihiro

#endif