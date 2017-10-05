set(POCO_PREFIX poco)
set(POCO_CONFIGURE_COMMAND "")
set(POCO_BUILD_COMMAND "")
set(POCO_INSTALL_COMMAND "")

if(WIN32)
	# Windows
	set(POCO_URL https://pocoproject.org/releases/poco-1.7.8/poco-1.7.8p3.zip)

	# Debug/Release
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(POCO_BUILD_COMMAND buildwin.cmd 140 build shared debug Win32 nosamples notests msbuild)
		set(POCO_LIBS PocoFoundationd.lib PocoJSONd.lib PocoNetd.lib PocoUtild.lib PocoXMLd.lib)
	else()
		set(POCO_BUILD_COMMAND buildwin.cmd 140 build shared release Win32 nosamples notests msbuild)
		set(POCO_LIBS PocoFoundation.lib PocoJSON.lib PocoNet.lib PocoUtil.lib PocoXML.lib)
	endif()
else(WIN32)
	#Linux
	set(POCO_URL https://pocoproject.org/releases/poco-1.7.8/poco-1.7.8p3.tar.gz)
	set(POCO_CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=install --no-tests --no-samples --typical --shared)
	set(POCO_BUILD_COMMAND make -s -j2)
	set(POCO_INSTALL_COMMAND make install)

	# Debug/Release
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(POCO_LIBS libPocoFoundationd.so libPocoJSONd.so PocoNetd.so libPocoUtild.so libPocoXMLd.so)
	else()
		set(POCO_LIBS libPocoFoundation.so libPocoJSON.so PocoNet.so libPocoUtil.so libPocoXML.so)
	endif()
endif(WIN32)

ExternalProject_Add(
	${POCO_PREFIX}
	PREFIX ${POCO_PREFIX}

	# Download
	URL ${POCO_URL}

	# Update
	UPDATE_COMMAND ""

	# Configure
	CONFIGURE_COMMAND ${POCO_CONFIGURE_COMMAND}

	# Build
	BUILD_IN_SOURCE 1
	BUILD_COMMAND ${POCO_BUILD_COMMAND}

	# Install
	INSTALL_COMMAND ${POCO_INSTALL_COMMAND}
)

ExternalProject_Get_Property(${POCO_PREFIX} SOURCE_DIR)
ExternalProject_Get_Property(${POCO_PREFIX} BINARY_DIR)
message(STATUS "${POCO_PREFIX} source directory: ${SOURCE_DIR}")
message(STATUS "${POCO_PREFIX} binary directory: ${BINARY_DIR}")

set(POCO_INCLUDE_DIRS
	${SOURCE_DIR}/CppUnit/include
	${SOURCE_DIR}/Foundation/include
	${SOURCE_DIR}/JSON/include
	${SOURCE_DIR}/Net/include
	${SOURCE_DIR}/Util/include
	${SOURCE_DIR}/XML/include
)
include_directories(${POCO_INCLUDE_DIRS})

if(WIN32)
	link_directories(${SOURCE_DIR}/lib)
else()
	link_directories(${SOURCE_DIR}/lib/Linux/x86_64)
endif()
