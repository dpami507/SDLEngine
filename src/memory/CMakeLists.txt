file(GLOB_RECURSE MEMORY_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(memory STATIC ${MEMORY_SOURCES})

target_include_directories(memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(memory PUBLIC core)