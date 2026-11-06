cmake_minimum_required(VERSION 3.20)
project(CourseworkPractice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Use the x64 MSVC toolset with the bundled Visual Studio SFML libraries.")
endif()

# Official SFML 2.6.2 vc17 x64 shared libraries, in both build configurations.
set(sfml_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.6.2")
foreach(module IN ITEMS system window graphics)
    add_library(sfml-${module} SHARED IMPORTED)
    set_target_properties(sfml-${module} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${sfml_dir}/include"
        IMPORTED_LOCATION "${sfml_dir}/bin/sfml-${module}-2.dll"
        IMPORTED_IMPLIB "${sfml_dir}/lib/sfml-${module}.lib"
        IMPORTED_LOCATION_DEBUG "${sfml_dir}/bin/sfml-${module}-d-2.dll"
        IMPORTED_IMPLIB_DEBUG "${sfml_dir}/lib/sfml-${module}-d.lib"
    )
endforeach()
target_link_libraries(sfml-window INTERFACE sfml-system)
target_link_libraries(sfml-graphics INTERFACE sfml-window)

add_subdirectory("lib/box2d")
set(B2D_INCS "${CMAKE_CURRENT_SOURCE_DIR}/lib/box2d/include")

add_library(engine STATIC engine/game_system.cpp engine/entity.cpp engine/renderer.cpp)
target_include_directories(engine PUBLIC engine)
target_link_libraries(engine PUBLIC sfml-graphics)

add_library(tile_level STATIC tile_level_loader/level_system.cpp)
target_include_directories(tile_level PUBLIC tile_level_loader)
target_link_libraries(tile_level PUBLIC sfml-graphics)

add_executable(coursework
    main.cpp
    scenes.cpp
    b2d_utils.cpp
)

target_link_libraries(coursework PRIVATE
    engine
    tile_level
    box2d
)
set_target_properties(coursework PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:coursework>"
)


add_custom_command(TARGET coursework POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:sfml-graphics>" "$<TARGET_FILE:sfml-window>" "$<TARGET_FILE:sfml-system>"
        "$<TARGET_FILE_DIR:coursework>"
    VERBATIM
)
