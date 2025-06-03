#include "../include/LogFormatter.h"
namespace chihiro {

// std::string LogFormatter::format(Logger::ptr logger, LogLevel::Level leverl, LogEvent::ptr event) {
//     std::stringstream ss;
//     // ss <<

//     std::string result = ss.str();
//     return result;
// }

std::string LogFormatter::format(LogLevel::Level leverl, LogEvent::ptr event) {
    std::stringstream ss;
    // ss <<

    std::string result = ss.str();
    return result;
}

LogFormatter::ptr LogAppender::getFormatter() const {
    return m_formatter;
}

} // namespace chihiro