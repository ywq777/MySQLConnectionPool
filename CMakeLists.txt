cmake_minimum_required(VERSION 3.24)
project(MySQLConnectionPool)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR D:\\tools\\MySQL\\MySQL\ Server\ 5.7\\include)
set(LINK_DIR D:\\tools\\MySQL\\MySQL\ Server\ 5.7\\lib)

#引入头文件s
include_directories(${INC_DIR})
#引入库文件
link_directories(${LINK_DIR})
link_libraries(libmysql)

add_executable(MySQLConnectionPool main.cpp Connection.cpp Connection.h CommonConnectionPool.cpp CommonConnectionPool.h public.h)

target_link_libraries(MySQLConnectionPool libmysql)