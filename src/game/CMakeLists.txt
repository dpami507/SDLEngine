file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(game STATIC ${GAME_SOURCES})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# core probably
target_link_libraries(game PUBLIC audio)
target_link_libraries(game PUBLIC core)
# target_link_libraries(game PUBLIC events)
target_link_libraries(game PUBLIC graphics)
target_link_libraries(game PUBLIC memory)