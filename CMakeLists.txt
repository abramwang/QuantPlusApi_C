project (Demo)

aux_source_directory(. DIR_SRCS)

# 添加 src 子目录
add_subdirectory(src)

add_executable(Demo ${DIR_SRCS})

# 添加链接库
target_link_libraries(Demo QP_Api)