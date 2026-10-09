file(GLOB_RECURSE AUDIO_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(audio STATIC ${AUDIO_SOURCES})

target_include_directories(audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(audio PUBLIC core)
target_link_libraries(audio PUBLIC memory)
# memory, core