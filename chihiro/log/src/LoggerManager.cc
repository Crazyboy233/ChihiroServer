#include "../include/LoggerManager.h"

namespace chihiro {
LoggerManager::LoggerManager() {

}

Logger::ptr LoggerManager::getLogger(const std::string & name) {

}

void LoggerManager::init() {

}

Logger::ptr LoggerManager::getRoot() const {
    return m_root;
}

} // namespace chihiro