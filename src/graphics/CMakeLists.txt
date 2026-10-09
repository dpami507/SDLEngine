file(GLOB_RECURSE GRAPHICS_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(graphics STATIC ${GRAPHICS_SOURCES})

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(graphics PUBLIC core)
target_link_libraries(graphics PUBLIC memory)
target_link_libraries(graphics PUBLIC SDL3::SDL3)
# shouldn't need game
target_link_libraries(graphics PUBLIC game)