cmake_minimum_required(VERSION 3.0)
project(libhttproute-poco)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

#find_package(libhttproute REQUIRED)
include_directories(../)

find_package(Poco REQUIRED)
include_directories(${POCO_FOUNDATION_INCLUDE_DIRS})
include_directories(${POCO_NET_INCLUDE_DIRS})
include_directories(${POCO_UTIL_INCLUDE_DIRS})

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

set(headers
	request.h
	routed_http_request_handler.h
)
set(sources
	request.cpp
	routed_http_request_handler.cpp
)
add_library(
	${PROJECT_NAME}
	STATIC
	${headers}
	${sources}
)
target_link_libraries(
	${PROJECT_NAME}
	${POCO_FOUNDATION_LIBRARY}
	${POCO_NET_LIBRARY}
	${POCO_UTIL_LIBRARY}
	${PROJECT_SOURCE_DIR}/../libhttproute/build/Debug/libhttproute.lib
)

#DEMO
add_executable(
	${PROJECT_NAME}_demo
	demo.cpp
)
target_link_libraries(
	${PROJECT_NAME}_demo
	${PROJECT_NAME}
	${POCO_FOUNDATION_LIBRARY}
	${POCO_NET_LIBRARY}
	${POCO_UTIL_LIBRARY}
	${PROJECT_SOURCE_DIR}/../libhttproute/build/Debug/libhttproute.lib
)