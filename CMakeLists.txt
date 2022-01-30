cmake_minimum_required(VERSION 3.12.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(angles LANGUAGES CXX)

option(ANG_MORE_WARNINGS "More compiler warnings" OFF)
option(ANG_WERROR "Compile with -Werror option" OFF)
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    message(STATUS
        "Setting build type to 'Release' as none was specified."
    )
    set(CMAKE_BUILD_TYPE "Release" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS "Debug" "Release"
    )
endif()

include(utils)

if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    ang_process_flag_availability(ANG_FMAX_ERRORS_100 "-fmax-errors=100" "")
    list(APPEND ANG_COMPILE_OPTIONS
        -Wall -Wextra -Wshadow -Wunused-result -Wno-unused-parameter
        -Wno-sign-conversion ${ANG_FMAX_ERRORS_100}
    )
    if(${ANG_WERROR})
        list(APPEND ANG_COMPILE_OPTIONS -Werror)
    endif()
    include(warnings)
    ang_add_more_warnings(ANG_COMPILE_OPTIONS)
endif()

find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

list(APPEND ANG_SOURCES
    "${CMAKE_SOURCE_DIR}/src/app.cpp"
    "${CMAKE_SOURCE_DIR}/src/batch_data.cpp"
    "${CMAKE_SOURCE_DIR}/src/color.cpp"
    "${CMAKE_SOURCE_DIR}/src/draw.cpp"
    "${CMAKE_SOURCE_DIR}/src/exception.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/ai.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/cell.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/field.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/game.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/line.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/search.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/searching_cell_record.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/state.cpp"
    "${CMAKE_SOURCE_DIR}/src/game/step.cpp"
    "${CMAKE_SOURCE_DIR}/src/iimg.cpp"
    "${CMAKE_SOURCE_DIR}/src/img_characters.cpp"
    "${CMAKE_SOURCE_DIR}/src/img_floor.cpp"
    "${CMAKE_SOURCE_DIR}/src/img_frames.cpp"
    "${CMAKE_SOURCE_DIR}/src/img_text.cpp"
    "${CMAKE_SOURCE_DIR}/src/keyboard.cpp"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/mouse.cpp"
    "${CMAKE_SOURCE_DIR}/src/res_keeper.cpp"
    "${CMAKE_SOURCE_DIR}/src/shader.cpp"
    "${CMAKE_SOURCE_DIR}/src/shader_program.cpp"
    "${CMAKE_SOURCE_DIR}/src/sprite.cpp"
    "${CMAKE_SOURCE_DIR}/src/spritesheet.cpp"
    "${CMAKE_SOURCE_DIR}/src/texture.cpp"
    "${CMAKE_SOURCE_DIR}/src/timer.cpp"
    "${CMAKE_SOURCE_DIR}/src/vao.cpp"
    "${CMAKE_SOURCE_DIR}/src/vbo.cpp"
    "${CMAKE_SOURCE_DIR}/src/vec2.cpp"
    "${CMAKE_SOURCE_DIR}/src/vertex_attribute_array.cpp"
    "${CMAKE_SOURCE_DIR}/src/window.cpp"
)

link_target(angles ${ANG_SOURCES})

set_target_properties(angles PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE 1
)

target_compile_options(angles PRIVATE ${ANG_COMPILE_OPTIONS})

target_link_libraries(angles PRIVATE
    ${GLEW_LIBRARIES}
    ${GLFW3_LIBRARY}
    ${OPENGL_LIBRARIES}
)

target_include_directories(angles PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    ${GLEW_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIR}
)
