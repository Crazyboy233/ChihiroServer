cmake_minimum_required(VERSION 3.10)
project(chihiro_log)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 第三方库头文件路径
set(UTF8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/chihiro)

# 头文件路径
set(LOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/chihiro/log/include)

# 源文件路径
set(LOG_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/chihiro/log/src)

# 给全局添加头文件路径
include_directories(
    ${LOG_INCLUDE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/chihiro
)

# 需要编译的源文件
set(LOG_SOURCES
    ${LOG_SRC_DIR}/LogLevel.cc
    ${LOG_SRC_DIR}/LogAppender.cc
    ${LOG_SRC_DIR}/LogEvent.cc
    ${LOG_SRC_DIR}/LogFormatter.cc
    ${LOG_SRC_DIR}/Logger.cc
)

# add_library(chihiro_log STATIC ${LOG_SOURCES})

add_executable(main chihiro/main.cpp ${LOG_SOURCES})

# target_link_libraries(main PRIVATE chihiro_log)

# target_include_directories(chihiro_log 
#     PUBLIC 
#     ${LOG_INCLUDE_DIR}
#     ${UTF8_INCLUDE_DIR}
# )