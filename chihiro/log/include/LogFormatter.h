#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include "Logger.h"
#include "LogEvent.h"
namespace chihiro {


// 日志格式器
class LogFormatter {
public:
    using ptr = std::shared_ptr<LogFormatter>;

    LogFormatter(const std::string & pattern);

    std::string format(Logger::ptr logger, LogLevel::Level leverl, LogEvent::ptr event);

    void init();

    bool isError() const { return m_error; }

    std::string getPattern() const { return m_pattern; }
public:
    // 具体日志格式项
    class FormatItem {
    public:
        using ptr = std::shared_ptr<FormatItem>;
        virtual ~FormatItem() {}

        virtual void format(std::ostream & os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };
private:
    std::string m_pattern;                  // 输出格式
    std::vector<FormatItem::ptr> m_items;   // 通过日志解析出来的格式项
    bool m_error = false;                   // 是否解析出错
};

} // namespace chihiro

#endif