project(BUILDER LANGUAGES CXX)

# 查找 Boost（根据需要调整版本和组件）
find_package(Boost REQUIRED COMPONENTS filesystem system)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS inc/*.h)

set(HTMLTAGET ${PROJECT_NAME}_html)
make_exe(${HTMLTAGET} ${HEADERS} src/html.cpp)