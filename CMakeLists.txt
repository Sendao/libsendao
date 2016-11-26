cmake_minimum_required (VERSION 2.8)
project(libsendao)

include_directories( "./include" )

export(PACKAGE sendao)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
add_library(sendao STATIC SHARED src/array.cpp src/attribs.cpp src/config.cpp src/io.cpp src/lists.cpp src/list.cpp src/maps.cpp src/objects.cpp src/string.cpp src/system.cpp src/tables.cpp src/util.cpp src/ptr.cpp)

install(TARGETS sendao
	EXPORT sendao
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib/static"
	)
install(DIRECTORY include/ DESTINATION include/sendao
	FILES_MATCHING PATTERN "*.h")
install(FILES sendaoConfig.cmake DESTINATION lib/cmake/sendao)
