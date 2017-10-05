set(LIBHTTPROUTE_PREFIX libhttproute)

ExternalProject_Add(
	${LIBHTTPROUTE_PREFIX}
	PREFIX ${LIBHTTPROUTE_PREFIX}

	GIT_REPOSITORY https://github.com/mfreiholz/libhttproute-cpp.git

	CMAKE_ARGS -DBuildShared=OFF -DBuildTests=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}

	INSTALL_COMMAND ""
)


ExternalProject_Get_Property(${LIBHTTPROUTE_PREFIX} SOURCE_DIR)
ExternalProject_Get_Property(${LIBHTTPROUTE_PREFIX} BINARY_DIR)
message(STATUS "${LIBHTTPROUTE_PREFIX} source directory: ${SOURCE_DIR}")
message(STATUS "${LIBHTTPROUTE_PREFIX} binary directory: ${BINARY_DIR}")


set(LIBHTTPROUTE_INCLUDE_DIRS ${SOURCE_DIR})
include_directories(${LIBHTTPROUTE_INCLUDE_DIRS})

set(LIBHTTPROUTE_LIBRARY_DIRS ${BINARY_DIR})
link_directories(${LIBHTTPROUTE_LIBRARY_DIRS})

if(WIN32)
	set(LIBHTTPROUTE_LIBS libhttproute.lib)
	set(LIBHTTPROUTE_LIBRARY libhttproute.lib)
else(WIN32)
	set(LIBHTTPROUTE_LIBS liblibhttproute.a)
	set(LIBHTTPROUTE_LIBRARY liblibhttproute.a)
endif(WIN32)
