include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)

if (NOT WIN32)
	set(COMMON_CXX_FLAGS "-fPIC -pedantic -fstack-protector -Wall -Wextra -Wcast-qual -Weffc++ -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
ELSE()
	set(COMMON_CXX_FLAGS "")
ENDIF()

set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -march=native -mtune=generic")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

IF(WIN32)
	add_executable(bot ${SRC})	
ELSE()
	add_executable(bot ${SRC} src/custom_methods/photos.hpp)
ENDIF()

find_library(cpp_vk_lib HINTS "../lib")

IF(WIN32)
	target_link_libraries(bot cpp_vk_lib unofficial::curlpp::curlpp)
ELSE()
  	target_link_libraries(bot cpp_vk_lib curlpp)
ENDIF()