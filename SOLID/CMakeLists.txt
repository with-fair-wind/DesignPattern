project(SOLID LANGUAGES CXX)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# 查找 Boost（根据需要调整版本和组件）
find_package(Boost REQUIRED COMPONENTS filesystem system)

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
