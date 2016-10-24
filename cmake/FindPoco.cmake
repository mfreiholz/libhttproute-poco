if(WIN32)
	# Foundation
	find_path(
		POCO_FOUNDATION_INCLUDE_DIRS
		NAMES Poco/Foundation.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Foundation/include/
	)
	find_library(
		POCO_FOUNDATION_LIBRARY_DEBUG
		NAMES PocoFoundationd
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	find_library(
		POCO_FOUNDATION_LIBRARY_RELEASE
		NAMES PocoFoundation
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	if(POCO_FOUNDATION_INCLUDE_DIRS AND POCO_FOUNDATION_LIBRARY_DEBUG AND POCO_FOUNDATION_LIBRARY_RELEASE)
		set(POCO_FOUNDATION_FOUND TRUE)
		set(
			POCO_FOUNDATION_LIBRARY
			debug ${POCO_FOUNDATION_LIBRARY_DEBUG}
			optimized ${POCO_FOUNDATION_LIBRARY_RELEASE}
		)
	endif()

	# Net
	find_path(
		POCO_NET_INCLUDE_DIRS
		NAMES Poco/Net/Net.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Net/include/
	)
	find_library(
		POCO_NET_LIBRARY_DEBUG
		NAMES PocoNetd.lib
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	find_library(
		POCO_NET_LIBRARY_RELEASE
		NAMES PocoNet.lib
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	if(POCO_NET_INCLUDE_DIRS AND POCO_NET_LIBRARY_DEBUG AND POCO_NET_LIBRARY_RELEASE)
		set(POCO_NET_FOUND TRUE)
		set(
			POCO_NET_LIBRARY
			debug ${POCO_NET_LIBRARY_DEBUG}
			optimized ${POCO_NET_LIBRARY_RELEASE}
		)
	endif()
	
	# Util
	find_path(
		POCO_UTIL_INCLUDE_DIRS
		NAMES Poco/Util/Util.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Util/include/
	)
	find_library(
		POCO_UTIL_LIBRARY_DEBUG
		NAMES PocoUtild.lib
		HINTS HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	find_library(
		POCO_UTIL_LIBRARY_RELEASE
		NAMES PocoUtil.lib
		HINTS HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	if(POCO_UTIL_INCLUDE_DIRS AND POCO_UTIL_LIBRARY_DEBUG AND POCO_UTIL_LIBRARY_RELEASE)
		set(POCO_UTIL_FOUND TRUE)
		set(
			POCO_UTIL_LIBRARY
			debug ${POCO_UTIL_LIBRARY_DEBUG}
			optimized ${POCO_UTIL_LIBRARY_RELEASE}
		)
	endif()

endif(WIN32)