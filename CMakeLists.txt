cmake_minimum_required(VERSION 4.2)
project(VisiX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

# ---------- VisiX UXML Library ----------

aux_source_directory(${CMAKE_SOURCE_DIR}/src/uxml/src UXML_LIBRARY_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/uxml/src/binding UXML_LIBRARY_SRC_LIST)
add_library(VisiXUxmlLibrary SHARED ${UXML_LIBRARY_SRC_LIST})

target_include_directories(VisiXUxmlLibrary
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src/include/uxml
    ${CMAKE_SOURCE_DIR}/src/include/uxml/binding
)
target_compile_definitions(VisiXUxmlLibrary
  PRIVATE VISIX_UXML_LIBRARY_EXPORTS
)
set_target_properties(VisiXUxmlLibrary PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

set_target_properties(VisiXUxmlLibrary PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# ---------- VisiX UXML Complier ----------

aux_source_directory(${CMAKE_SOURCE_DIR}/src/uxml-complier/src UXML_COMPLIER_SRC_LIST)
add_executable(VisiXUxmlComplier ${UXML_COMPLIER_SRC_LIST})
target_link_libraries(VisiXUxmlComplier PRIVATE VisiXUxmlLibrary)
set_target_properties(VisiXUxmlComplier PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ---------- VisiX SDK ----------
aux_source_directory(${CMAKE_SOURCE_DIR}/src/sdk/src SDK_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/sdk/src/application SDK_SRC_LIST)
add_library(VisiXSdk SHARED ${SDK_SRC_LIST})
target_include_directories(VisiXSdk
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src/include/sdk
    ${CMAKE_SOURCE_DIR}/src/include/sdk/application
)
target_compile_definitions(VisiXSdk
  PRIVATE VISIX_SDK_EXPORTS
)

set_target_properties(VisiXSdk PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

set_target_properties(VisiXSdk PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# ---------- Test Preparing ----------
set(TEST_MATERIAL_DIR material)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/tests/${TEST_MATERIAL_DIR}
  ${CMAKE_BINARY_DIR}/bin/tests/${TEST_MATERIAL_DIR}
)
