#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include "LogEvent.h"
#include <vector>

namespace chihiro {

// 日志格式器
class LogFormatter {
public:
    using ptr = std::shared_ptr<LogFormatter>;

    virtual std::string format(const LogEvent::ptr& event) = 0;

    virtual ~LogFormatter() = default;
};

// 简单的模式格式化
class PatternFormatter : public LogFormatter {
public: 
    using ptr = std::shared_ptr<PatternFormatter>;

    PatternFormatter(const std::string & pattern);
    
    std::string format(const LogEvent::ptr& event) override;

    bool isError() const;

public:
    class FormatItem {
    public:
        using ptr = std::shared_ptr<FormatItem>;
        virtual ~FormatItem() = default;
        virtual void format(std::ostream& os, const LogEvent::ptr& event) = 0;
    };

private:
    // 解析格式字符串并初始化 items_
    void init();

    std::string m_pattern;                  // 输出格式
    std::vector<FormatItem::ptr> m_items;   // 解析后的格式化列表
    bool m_error;                   // 是否解析出错
};

} // namespace chihiro

#endif