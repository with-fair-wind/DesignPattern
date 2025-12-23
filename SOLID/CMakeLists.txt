project(SOLID LANGUAGES CXX)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# 查找 Boost（根据需要调整版本和组件）
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Boost.DI 是 header-only 的独立库（boost-ext/di），并非 Boost 官方组件。
# 用 FetchContent 拉取，避免依赖本机安装的 boost_diConfig.cmake。
include(FetchContent)

if(POLICY CMP0169)
    cmake_policy(SET CMP0169 OLD)
endif()

FetchContent_Declare(
    boost_di
    GIT_REPOSITORY https://github.com/boost-ext/di.git
    GIT_TAG v1.3.0
)

# boost-ext/di 是 header-only；只需要把源码拉下来加 include 路径即可。
# 直接 MakeAvailable() 会执行其子工程 CMakeLists.txt，而该仓库的 cmake_minimum_required
# 版本过老，在新版本 CMake 下可能直接报错（你现在遇到的就是这个）。
FetchContent_GetProperties(boost_di)

if(NOT boost_di_POPULATED)
    FetchContent_Populate(boost_di)
endif()

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS inc/*.h)

set(SRPTARGET ${PROJECT_NAME}_srp)
make_exe(${SRPTARGET} ${HEADERS} src/srp.cpp)
target_include_directories(
    ${SRPTARGET}
    PRIVATE
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(
    ${SRPTARGET}
    PRIVATE
    Boost::filesystem
    Boost::system
)

set(OCPTARGET ${PROJECT_NAME}_ocp)
make_exe(${OCPTARGET} ${HEADERS} src/ocp.cpp)

set(LSPTARGET ${PROJECT_NAME}_lsp)
make_exe(${LSPTARGET} ${HEADERS} src/lsp.cpp)

set(ISPTARGET ${PROJECT_NAME}_isp)
make_exe(${ISPTARGET} ${HEADERS} src/isp.cpp)

set(DIPTARGET ${PROJECT_NAME}_dip)
make_exe(${DIPTARGET} ${HEADERS} src/dip.cpp)
target_include_directories(
    ${DIPTARGET}
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${boost_di_SOURCE_DIR}/include
)