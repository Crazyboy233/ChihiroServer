#ifndef __CHIHIRO_LOGGERMANAGER_H__
#define __CHIHIRO_LOGGERMANAGER_H__

#include "Logger.h"
#include <map>
namespace chihiro {

class LoggerManager {
public:
    using ptr = std::shared_ptr<LoggerManager>;
    LoggerManager();
    // 获取日志器，如果原来没有，就创建一个默认日志器。
    Logger::ptr getLogger(const std::string & name);

    void init();

    Logger::ptr getRoot() const;
private:
    std::map<std::string, Logger::ptr> m_loggers;   // 日志器集合
    Logger::ptr m_root;                              // 默认日志器
};


} // namespace chihiro

#endif