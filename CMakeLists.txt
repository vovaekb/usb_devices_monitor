cmake_minimum_required(VERSION 3.16.0)

project(usb_devices_monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -pthread")
# -ludev

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET libusb-1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS)

# set include/ as include directory
include_directories(
        ${CONAN_INCLUDE_DIRS} 
        "include"
) 

# add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add_executable(test test.cpp)
# target_link_libraries(test PkgConfig::deps)

# add_executable(monitor_devs monitor_usb_devices)
# target_link_libraries(monitor_devs PkgConfig::deps udev)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        CONAN_PKG::nlohmann_json
        PkgConfig::deps
        udev
)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION lib) 
install(DIRECTORY include/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# test
add_subdirectory(test)

