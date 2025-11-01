cmake_minimum_required(VERSION 3.30)

# Vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(s3glr VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Dependencies (from vcpkg) ---

# glad (manual integration since no CMake config shipped)
find_path(GLAD_INCLUDE_DIRS NAMES glad/gl.h glad/glad.h)
find_library(GLAD_LIBRARIES NAMES glad)

if(NOT GLAD_INCLUDE_DIRS OR NOT GLAD_LIBRARIES)
    message(FATAL_ERROR "GLAD not found via vcpkg (check include and lib paths)")
endif()

# Wrap into an imported target for consistency
add_library(glad::glad INTERFACE IMPORTED)
set_target_properties(glad::glad PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GLAD_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${GLAD_LIBRARIES}"
)

# other packages (all provide CMake configs)
find_package(imgui CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
# stb is header-only (no targets in vcpkg)
find_path(Stb_INCLUDE_DIRS "stb_c_lexer.h")
find_package(assimp CONFIG REQUIRED)

if(NOT Stb_INCLUDE_DIRS)
    message(FATAL_ERROR "stb not found in vcpkg")
endif()

add_library(Stb::Stb INTERFACE IMPORTED)
set_target_properties(Stb::Stb PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Stb_INCLUDE_DIRS}"
)

# No C++20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# --- Executable ---
add_executable(s3glr)

# Sources
file(GLOB_RECURSE S3GLR_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)
target_sources(s3glr PRIVATE ${S3GLR_SOURCES})
if(MSVC)
    target_sources(s3glr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/icon.rc)
elseif(MINGW)
    enable_language(RC)
    target_sources(s3glr PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/icon.rc)
endif()

# Includes
target_include_directories(s3glr PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Stb_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Vender/Metal
)

# Defines
target_compile_definitions(s3glr PRIVATE
    MY_TEST_DEFINE
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # --- Link libraries ---
    message("----INFO: BUILDING FOR WINDOWS----")
    target_link_libraries(s3glr PRIVATE
        glad::glad
        imgui::imgui
        OpenAL::OpenAL
        glm::glm
        nlohmann_json::nlohmann_json
        glfw
        Stb::Stb
        assimp::assimp
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # --- Link libraries --- 
    message("----INFO: BUILDING FOR MAC----")
    target_link_libraries(s3glr PRIVATE
        glad::glad
        imgui::imgui
        OpenAL::OpenAL
        glm::glm
        nlohmann_json::nlohmann_json
        glfw
        Stb::Stb
        assimp::assimp
        "-framework Metal"
        "-framework QuartzCore"
        "-framework Cocoa"
    )
endif()

# --- Compiler warnings ---
if(MSVC)
    target_compile_options(s3glr PRIVATE
        /W3
        /MP
        /WX
        /ZI
    )
else()
    target_compile_options(s3glr PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# --- Visual Studio niceties ---
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT s3glr)
set_target_properties(s3glr PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${S3GLR_SOURCES})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
