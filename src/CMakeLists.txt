###
###

PROJECT(QP_Api)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)

###输出路径
SET(LIBRARY_OUTPUT_PATH ../LIB)


###头文件路径
INCLUDE_DIRECTORIES(
F:\04系统编码\03tag\QuantApi-beta5.1.4\PT_QuantApi\include
)

###链接库路径
LINK_DIRECTORIES(
F:\04系统编码\03tag\QuantApi-beta5.1.4\PT_QuantApi\bin\lib-x64-msvc-12.0-Debug
)

###生成静态库
ADD_LIBRARY(QP_Api STATIC ${SRC_LIST})


TARGET_LINK_LIBRARIES(QP_Api PT_QuantApi)