cmake_minimum_required(VERSION 3.0)
project(libhttproute-poco)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

find_package(Poco REQUIRED)
include_directories(${POCO_FOUNDATION_INCLUDE_DIRS})
include_directories(${POCO_NET_INCLUDE_DIRS})
include_directories(${POCO_UTIL_INCLUDE_DIRS})

find_package(LibHttpRoute REQUIRED)
include_directories(${LIBHTTPROUTE_INCLUDE_DIRS})

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_library(
	${PROJECT_NAME}
	STATIC
	${PROJECT_NAME}/request.h
	${PROJECT_NAME}/routed_http_request_handler.h
	${PROJECT_NAME}/request.cpp
	${PROJECT_NAME}/routed_http_request_handler.cpp
)
target_link_libraries(
	${PROJECT_NAME}
	${POCO_FOUNDATION_LIBRARY}
	${POCO_NET_LIBRARY}
	${POCO_UTIL_LIBRARY}
	${LIBHTTPROUTE_LIBRARY}
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
	${POCO_FOUNDATION_LIBRARY}
	${POCO_NET_LIBRARY}
	${POCO_UTIL_LIBRARY}
)