cmake_minimum_required(VERSION 3.10)
project(chihiro_log)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOG_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/chihiro/log/src)
set(LOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/chihiro/log/include)

# 明确指定编译顺序
set(LOG_SOURCES
    ${LOG_SRC_DIR}/LogLevel.cc
    ${LOG_SRC_DIR}/LogAppender.cc
    ${LOG_SRC_DIR}/Logger.cc
    ${LOG_SRC_DIR}/LogEvent.cc
    ${LOG_SRC_DIR}/LogFormatter.cc
)

add_library(chihiro_log STATIC ${LOG_SOURCES})

target_include_directories(chihiro_log 
    PUBLIC 
    ${LOG_INCLUDE_DIR}
)