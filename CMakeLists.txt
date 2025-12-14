cmake_minimum_required(VERSION 4.2)

project(VisiX)

set(VCPKG_PATH "C:/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")


set(GENERAL_INCLUDE "${VCPKG_PATH}/installed/x64-windows/include")
include_directories("${GENERAL_INCLUDE}")

include_directories(src/uxml)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/uxml SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/uxml/binding SRC_LIST)
add_executable (${PROJECT_NAME} ${SRC_LIST})
