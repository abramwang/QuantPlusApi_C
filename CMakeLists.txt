####
####

PROJECT(demo)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)

#输出路径
#SET(EXECUTABLE_OUTPUT_PATH ../bin)

#头文件路径
INCLUDE_DIRECTORIES(
F:\QuantPlusApi_C\QuantPlusApi_C-master\src
)
#链接库路径
LINK_DIRECTORIES(
F:\QuantPlusApi_C\QuantPlusApi_C-master\src\LIB\Debug
F:\04系统编码\03tag\QuantApi-beta5.1.4\PT_QuantApi\bin\lib-x64-msvc-12.0-Debug
)

ADD_EXECUTABLE(demo ${SRC_LIST})

TARGET_LINK_LIBRARIES(demo QP_Api)