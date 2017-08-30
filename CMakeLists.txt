cmake_minimum_required(VERSION 3.0)
project(libhttproute-poco)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

include(ExternalProject)
include(vendor/libhttproute.cmake)
include(vendor/poco.cmake)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_library(
	${PROJECT_NAME}
	STATIC
	${PROJECT_NAME}/libhttproute-poco.h
	${PROJECT_NAME}/libhttproute-poco.cpp
)
target_link_libraries(
	${PROJECT_NAME}
	${LIBHTTPROUTE_LIBS}
	${POCO_LIBS}
)
add_dependencies(
	${PROJECT_NAME}
	libhttproute
	pocoproject
)

# demo binary
include_directories(${PROJECT_NAME})
add_executable(
	${PROJECT_NAME}_demo
	demo/server.cpp
)
target_link_libraries(
	${PROJECT_NAME}_demo
	${PROJECT_NAME}
	${LIBHTTPROUTE_LIBS}
	${POCO_LIBS}
)