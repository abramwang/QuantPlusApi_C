link_directories("D:/Develop/git/QuantPlus/APIS/include")
link_libraries("D:/Develop/git/QuantPlus/APIS/lib-x64-msvc-12.0-Release")
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
add_library (QP_Api ${DIR_LIB_SRCS})
target_link_libraries(QP_Api PT_QuantApi)