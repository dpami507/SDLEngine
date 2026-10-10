file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(events STATIC ${GAME_SOURCES})

target_include_directories(events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(events PUBLIC memory)
target_link_libraries(events PUBLIC SDL3::SDL3)
target_link_libraries(events PUBLIC core)