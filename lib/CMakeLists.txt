include_directories(../dependencies)
include_directories(../dependencies/spdlog/include)
include_directories(../dependencies/curlpp/include)
include_directories(include/cpp_vk_lib)

add_definitions(-DVK_CURL_DEBUG)
add_definitions(-DAPI_V="5.130")

set(extra_warnings TRUE)
set(find_leaks FALSE)

set(common_flags "-fPIC -Wall -Wextra -pedantic -Wshadow -Wunused-parameter")

if (${find_leaks})
  set(find_leaks_flags "-fsanitize=leak -fstack-protector")
else()
  set(find_leaks_flags "")
endif()

if (${extra_warnings})
  set(extra_warnings_flags "-Wcast-qual -Wnon-virtual-dtor -Wreturn-type -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
  set(extra_warnings_flags "")
endif()

IF (NOT WIN32)
  set(CMAKE_CXX_FLAGS "${common_flags} ${extra_warnings_flags} ${find_leaks_flags} -O2 -msse3 -march=native -mtune=generic -flto")
endif()

add_library(lib-simdjson INTERFACE)
target_compile_features(lib-simdjson INTERFACE cxx_std_17)
target_include_directories(lib-simdjson INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCDIR}>)
install(TARGETS lib-simdjson EXPORT simdjson-config INCLUDES DESTINATION dependencies)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_library(cpp_vk_lib SHARED ${SRC})

IF(WIN32)
  find_package(CURL CONFIG REQUIRED) #vcpkg moment)
  find_package(unofficial-curlpp CONFIG REQUIRED)

  target_link_libraries(cpp_vk_lib PRIVATE simdjson CURL::libcurl unofficial::curlpp::curlpp)
ELSE()
  target_link_libraries(cpp_vk_lib simdjson)
ENDIF()