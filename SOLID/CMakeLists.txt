project(SOLID LANGUAGES CXX)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

# 查找 Boost（根据需要调整版本和组件）
find_package(Boost REQUIRED COMPONENTS filesystem system)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS inc/*.h)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Boost::filesystem
    Boost::system
)
target_precompile_headers(${PROJECT_NAME} PRIVATE inc/pch.h)