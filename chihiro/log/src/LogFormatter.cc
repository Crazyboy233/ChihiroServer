#include "LogFormatter.h"
#include "UTF8/utf8.h"
#include <sstream>
#include <chrono>

namespace chihiro {

PatternFormatter::PatternFormatter(const std::string & pattern)
    : m_pattern(pattern) 
    , m_error(false)
{
    this->init();
}

std::string PatternFormatter::format(const LogEvent::ptr& event) {
    std::ostringstream oss;
    for(auto item : m_items) {
        item->format(oss, event);
    }
    return oss.str();
}

bool PatternFormatter::isError() const {
    return m_error;
}

void PatternFormatter::init() {
    // 格式解析状态机
    enum class ParseState {
        Normal,     // 普通文本
        Percent,    // 遇到 % 符号
        Format      // 解析格式指令
    };

    ParseState state = ParseState::Normal;
    std::string fmt;

    std::string::iterator it = m_pattern.begin();
    while (it != m_pattern.end()) {
        uint32_t codePoint = utf8::next(it, m_pattern.end());

        std::string str;    // 准备存放字符的 str
        utf8::append(codePoint, std::back_insert_iterator(str));
        
        // 输出字符
        // std::cout << "字符: " << str << std::endl;
    }
}


// 时间格式化项
class DateTimeFormatItem : public PatternFormatter::FormatItem {
public:
    // explicit DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S") {}

    void format(std::ostream& os, const LogEvent::ptr& event) override {
        // std::time_t timestamp = event->getTime();
        // auto time_point = std::chrono::system_clock::from_time_t(timestamp);
        os << event->getTime();
    }
};


// 日志级别格式化项
class LevelFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getLevelStr();
    }    
};


// 日志消息格式化项
class MessageFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getContent();
    }
};


// 文件名格式化项
class FileNameFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getFileName();
    }
};


// 行号格式化项
class LineNumberFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getLine();
    }
};


// 线程ID格式化项
class ThreadIDFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getThreadId();
    }
};


// 协程ID格式化项
class FiberIDFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getFiberId();
    }
};

} // namespace chihiro