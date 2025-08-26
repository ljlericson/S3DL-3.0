cmake_minimum_required(VERSION 3.15)
project(TestApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Game/Game.cpp
    src/Utils/Timer.cpp
)


# ImGui sources
set(IMGUI_SRC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Executable
add_executable(s3gl ${SOURCES})

target_include_directories(s3gl PRIVATE
    external/imgui
    external/imgui/backends
)

# Libraries
target_link_libraries(s3gl PRIVATE
    OpenAL32
    glfw3
    glew32
    opengl32l
    gdi32
) 