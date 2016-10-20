if(WIN32)
	# Foundation
	find_path(
		POCO_FOUNDATION_INCLUDE_DIRS
		NAMES Poco/Foundation.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Foundation/include/
	)
	find_library(
		POCO_FOUNDATION_LIBRARY
		NAMES PocoFoundationd.lib
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	# Net
	find_path(
		POCO_NET_INCLUDE_DIRS
		NAMES Poco/Net/Net.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Net/include/
	)
	find_library(
		POCO_NET_LIBRARY
		NAMES PocoNetd.lib
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	# Util
	find_path(
		POCO_UTIL_INCLUDE_DIRS
		NAMES Poco/Util/Util.h
		HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/Util/include/
	)
	find_library(
		POCO_UTIL_LIBRARY
		NAMES PocoUtild.lib
		HINTS HINTS ${PROJECT_SOURCE_DIR}/../_vendor-src/poco-1.7.5/lib/
	)
	
	if(POCO_FOUNDATION_LIBRARY AND POCO_NET_LIBRARY AND POCO_UTIL_LIBRARY)
		set(POCO_FOUND TRUE)
	endif()
endif(WIN32)