cmake_minimum_required(VERSION 3.20)
project(bh-renderer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(bh_core INTERFACE)
target_include_directories(bh_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bh-renderer src/main.cpp)
target_link_libraries(bh-renderer PRIVATE bh_core)

# Vulkan は任意: 見つからない環境 (CI の検証等) では物理ヘッダと
# テストだけをビルドする。
find_package(Vulkan QUIET)
if(Vulkan_FOUND)
  message(STATUS "Vulkan found: ${Vulkan_LIBRARY}")
  target_compile_definitions(bh-renderer PRIVATE BH_HAS_VULKAN=1)
else()
  message(STATUS "Vulkan not found: building core library and tests only")
endif()

enable_testing()
add_executable(test_physics tests/test_physics.cpp)
target_link_libraries(test_physics PRIVATE bh_core)
add_test(NAME physics COMMAND test_physics)
