#include "LogFormatter.h"
#include <sstream>
namespace chihiro {

class LiteralFormatItem;
class DateTimeFormatItem;
class LevelFormatItem;
class MessageFormatItem;
class FileNameFormatItem;
class LineNumberFormatItem;
class ThreadIDFormatItem;
class FiberIDFormatItem;


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
    oss << std::endl;
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
    std::string fmt;    // 存储指令格式，例如 "d","p"
    std::string str;    // 存储普通文本

    for(auto ch : m_pattern) {
        switch(state) {
            case ParseState::Normal:
                if (ch == '%') {
                    if(!str.empty()) {
                        m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<LiteralFormatItem>(str)));
                        str.clear();
                    }
                    state = ParseState::Percent;
                } else {
                    str += ch;
                }
                break;

            case ParseState::Percent:
                if(ch == '%') {
                    // %% 转义为 %
                    str = "%";
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<LiteralFormatItem>(str)));
                    str.clear();
                    state = ParseState::Normal;
                    break;
                } else {
                    // 记录指令格式
                    fmt = ch;
                    state = ParseState::Format;
                }
                // break;
                // 此处不能执行break，否则会导致需要解析的格式字符串(如"p","m","n")后一位不做任何处理。

            case ParseState::Format:
                // 指令格式解析完成
                if(fmt == "d") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<DateTimeFormatItem>()));
                } else if(fmt == "p") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<LevelFormatItem>()));
                } else if(fmt == "m") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<MessageFormatItem>()));
                } else if(fmt == "f") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<FileNameFormatItem>()));
                } else if(fmt == "l") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<LineNumberFormatItem>()));
                } else if(fmt == "t") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<ThreadIDFormatItem>()));
                } else if(fmt == "n") {
                    m_items.push_back(std::static_pointer_cast<FormatItem>(std::make_shared<LiteralFormatItem>("\n")));
                } else {
                    m_error = true;
                }
                state = ParseState::Normal;
                break;
        }   
    }
}


// 静态文本格式化项,例如 []
class LiteralFormatItem : public PatternFormatter::FormatItem {
public:
    LiteralFormatItem(const std::string& literal) : m_literal(literal) {}

    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << m_literal << " ";
    }
private:
    std::string m_literal;
};


// 时间格式化项
class DateTimeFormatItem : public PatternFormatter::FormatItem {
public:
    // explicit DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S") {}

    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getTime() << " ";
    }
};


// 日志级别格式化项
class LevelFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getLevelStr() << " ";
    }    
};


// 日志消息格式化项
class MessageFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << "\"" << event->getContent() << "\" ";
    }
};


// 文件名格式化项
class FileNameFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getFileName() << " ";
    }
};


// 行号格式化项
class LineNumberFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getLine() << " ";
    }
};


// 线程ID格式化项
class ThreadIDFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getThreadId() << " ";
    }
};


// 协程ID格式化项
class FiberIDFormatItem : public PatternFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent::ptr& event) override {
        os << event->getFiberId() << " ";
    }
};

} // namespace chihiro