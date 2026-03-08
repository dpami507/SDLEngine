cmake_minimum_required (VERSION 3.8)
project ("SDLProject")

# =================================================
# DOWNLOAD DEPENDENCIES
# =================================================
#Add SDL
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

# Add source to this project's executable.
add_executable (SDLProject "main.cpp" "src/Vector2.cpp" "src/Vector2.h" "src/GameObject.cpp" "src/GameObject.h" "src/Sprite.cpp" "src/Sprite.h" "src/Game.cpp" "src/Game.h" "src/MemoryTracker.cpp" "src/Tracked.h" "src/Tracked.cpp" "src/GameObjectManager.h" "src/GameObjectManager.cpp" "src/Debug.cpp" "src/Debug.h" "src/GraphicsSystem.h" "src/GraphicsSystem.cpp" "src/Color.h" "src/Color.cpp")

# Interface library
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads REQUIRED)
target_link_libraries(asio INTERFACE Threads::Threads)

# Link SDL3 library and asio
target_link_libraries(SDLProject PRIVATE SDL3::SDL3)
target_link_libraries(SDLProject PUBLIC asio)

# Show SDL3.dll file so CMake can like work lol
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
