cmake_minimum_required(VERSION 3.28)

# Setup the project
project(steamdeck-app-demo LANGUAGES CXX)

# Set the C++ language standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ImGui directories
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_BACKENDS ${IMGUI_DIR}/backends)

# Add your source files here
set(SOURCES
    # Imgui sources
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_BACKENDS}/imgui_impl_sdl3.cpp
    ${IMGUI_BACKENDS}/imgui_impl_sdlrenderer3.cpp

    # Add your source files here
    src/main.cpp
    src/Application.cpp
    # ...
)

# Find packages and libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add additional include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_BACKENDS}
    ${SDL3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# Link the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL3_LIBRARIES}
)

# Sepcify compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
    ${SDL3_CFLAGS_OTHER}
)

# Install binary to system
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)