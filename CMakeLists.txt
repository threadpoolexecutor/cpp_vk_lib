cmake_minimum_required(VERSION 3.19)

project(cpp_vk_lib DESCRIPTION "C++ vk library" LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)
set(EXECUTABLE_OUTPUT_PATH ../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

IF(WIN32)
	find_package(CURL CONFIG REQUIRED)
	find_package(unofficial-curlpp CONFIG REQUIRED)
	find_package(GTest CONFIG REQUIRED)
	find_package(simdjson CONFIG REQUIRED)
	find_package(spdlog CONFIG REQUIRED)
ENDIF()

IF(NOT WIN32)
add_subdirectory(dependencies)
ENDIF()
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(bot)