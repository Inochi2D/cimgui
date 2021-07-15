cmake_minimum_required(VERSION 3.1)

project(cimgui)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()


#general settings
file(GLOB IMGUI_SOURCES
    cimgui.cpp
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
	${TABLES_SOURCE}
)

set(IMGUI_STATIC "no" CACHE STRING "Build as a static library")
set(IMGUI_FREETYPE "no" CACHE STRING "Build with freetype library")
set(IMGUI_FREETYPE_IN_TREE "no" CACHE STRING "freetype library is being build in-tree")
set(IMGUI_LIBRARIES )

if(IMGUI_FREETYPE)
    if (NOT IMGUI_FREETYPE_IN_TREE)
        FIND_PACKAGE(freetype REQUIRED PATHS ${FREETYPE_PATH})
    endif ()

    list(APPEND IMGUI_LIBRARIES freetype)
    list(APPEND IMGUI_SOURCES imgui/misc/freetype/imgui_freetype.cpp)
    add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)

#add library and link
if (IMGUI_STATIC)
    add_library(cimgui STATIC ${IMGUI_SOURCES})
else (IMGUI_STATIC)
    add_library(cimgui SHARED ${IMGUI_SOURCES})
endif (IMGUI_STATIC)

target_compile_definitions(cimgui PUBLIC IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1)
if (WIN32)
    target_compile_definitions(cimgui PUBLIC IMGUI_IMPL_API=extern\t\"C\"\t__declspec\(dllexport\))
    list(APPEND IMGUI_LIBRARIES imm32)
else (WIN32)
    target_compile_definitions(cimgui PUBLIC IMGUI_IMPL_API=extern\t\"C\"\t)
endif (WIN32)

set(IMGUI_SDL_IN_TREE "no" CACHE STRING "SDL library is being build in-tree")
set(IMGUI_SDL "no" CACHE STRING "Build with SDL")
set(IMGUI_OPENGL2 "no" CACHE STRING "Build with OpenGL2")
set(IMGUI_OPENGL3 "no" CACHE STRING "Build with OpenGL3")

if (IMGUI_SDL)
    if (NOT IMGUI_SDL_IN_TREE)
        FIND_PACKAGE(sdl2 REQUIRED PATHS ${sdl2_PATH})
    endif ()

    target_sources(cimgui
    PRIVATE
        imgui/backends/imgui_impl_sdl.cpp
        imgui/backends/imgui_impl_sdl.h
    )

    target_link_libraries(cimgui PRIVATE SDL2)
endif()

if (IMGUI_OPENGL2)
    target_sources(cimgui
    PRIVATE
        imgui/backends/imgui_impl_opengl2.cpp
        imgui/backends/imgui_impl_opengl2.h
    )
endif()

if (IMGUI_OPENGL3)
    target_sources(cimgui
    PRIVATE
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3.h
    )

    target_link_libraries(cimgui PRIVATE glbinding)
endif()

target_include_directories(cimgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cimgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set_target_properties(cimgui PROPERTIES PREFIX "")
target_link_libraries(cimgui PUBLIC ${IMGUI_LIBRARIES})

#install
install(TARGETS cimgui
    RUNTIME DESTINATION  .
    LIBRARY DESTINATION  .
    ARCHIVE DESTINATION  .
)

#test
set(CIMGUI_TEST "no" CACHE STRING "Enable compilation of a test unit based on imgui null")

if (CIMGUI_TEST)
  add_subdirectory(test)
endif ()
