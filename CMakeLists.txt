cmake_minimum_required (VERSION 3.16)
project ("SDLProject")

# cpp 23
set(CMAKE_CXX_STANDARD 23)

# =================================================
# DOWNLOAD DEPENDENCIES
# =================================================
#Add SDL3
message("Downloading SDL3... Do not stop the process, it may take a while...")
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SDL3)

# Add standalone Asio
message("Downloading Asio... Do not stop the process, it may take a while...")
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-30-2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(asio)

# =================================================
# CREATE LIBRARIES
# =================================================

add_subdirectory(src/audio)
add_subdirectory(src/core)
add_subdirectory(src/events)
add_subdirectory(src/game)
add_subdirectory(src/graphics)
add_subdirectory(src/memory)

# Add source to this project's executable.
add_executable (SDLProject "main.cpp")

# Interface library
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads REQUIRED)
target_link_libraries(asio INTERFACE Threads::Threads)

# Link SDL3 library and asio
target_link_libraries(SDLProject PRIVATE SDL3::SDL3)
target_link_libraries(SDLProject PUBLIC asio)
target_link_libraries(SDLProject PRIVATE audio core game graphics memory)

# Show SDL3_mixer.dll file so CMake can like work lol
add_custom_command(TARGET SDLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:SDLProject>
)

# Add resource folder as a directory
add_custom_command(TARGET SDLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:SDLProject>/resources)

target_compile_definitions(SDLProject PRIVATE SDL_MAIN_USE_CALLBACKS)
