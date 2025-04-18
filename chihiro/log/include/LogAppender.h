#ifndef __CHIHIRO_LOGAPPENDER_H__
#define __CHIHIRO_LOGAPPENDER_H__

#include "LogFormatter.h"
#include "LogLevel.h"
#include "LogEvent.h"
#include <sstream>
#include <fstream>

namespace chihiro {

class Logger;
class LogEvent;

// 日志输出地
class LogAppender {
public:
    using ptr = std::shared_ptr<LogAppender>;

    virtual ~LogAppender();  // 可能有很多输出地，所以设置为虚析构函数
    
    virtual void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) = 0;

    // 设置输出格式
    void setFormatter(LogFormatter::ptr format);
    // 获取输出格式
    LogFormatter::ptr getFormatter() const;

// 保护权限，保证派生类可以访问
protected:
    LogLevel::Level m_level;        // 日志级别
    LogFormatter::ptr m_formatter;  // 输出格式器
};

// 输出到控制台
class StdoutLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;

    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
private:
};

// 输出到文件
class FileLogAppender : public LogAppender {
public:
    using ptr = std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string & filename);

    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

    /// @brief 重新打开文件
    /// @return 成功返回True，失败返回False
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

} // namespace chihiro

#endif