cmake_minimum_required (VERSION 3.17)

project (Ludo VERSION 0.0.1 LANGUAGES CXX C)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


################
# Include GTest

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


################
# Include GFLW

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw-3.3.2)


################
# Main Include
add_executable(Ludo 
    src/c++17/Counter/Counter.cpp 
    src/c++17/Player/Player.cpp 
    src/c++17/Space/Space.cpp 
    src/c++17/HomeRun/HomeRun.cpp 
    src/c++17/Board/Board.cpp 
    src/c++17/Game/Game.cpp
    src/c++17/main.cpp
)


################
# GLEW Include

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES 
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew-2.1.0/lib/Release/x64/glew32s.lib
    INTERFACE_INCLUDE_DIRECTORIES  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew-2.1.0/include
)
add_definitions(-DGLEW_STATIC)


################
# IMGUI Include

add_library (imgui
    vendor/imgui-1.78/imgui.cpp
    vendor/imgui-1.78/imgui_draw.cpp
    vendor/imgui-1.78/imgui_widgets.cpp
    vendor/imgui-1.78/imgui_demo.cpp
)
add_library(imgui::imgui ALIAS imgui)

target_include_directories(imgui PUBLIC vendor/imgui-1.78/ vendor/imgui-1.78/examples/)
target_link_libraries(imgui PRIVATE glew )
#target_link_libraries(imgui PRIVATE glfw) 


add_library (imgui-win32 OBJECT
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-1.78/examples/imgui_impl_win32.cpp"
)

target_link_libraries (imgui-win32 PUBLIC imgui)
target_include_directories (imgui-win32 PUBLIC vendor/imgui-1.78/examples/)

add_library (imgui-glfw OBJECT
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-1.78/examples/imgui_impl_glfw.cpp"
)

#find_package (GLEW)

add_library (imgui-opengl OBJECT
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-1.78/examples/imgui_impl_opengl3.cpp"
)

target_link_libraries (imgui-opengl PUBLIC
    imgui
    "${OPENGL_gl_LIBRARY}"
    glew
)

target_include_directories (imgui-opengl PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories (imgui-opengl SYSTEM PUBLIC "${OPENGL_INCLUDE_DIR}")


target_link_libraries (imgui-glfw PUBLIC imgui glfw)
target_include_directories (imgui-glfw PUBLIC "${CMAKE_CURRENT_LIST_DIR}")


target_link_libraries (Ludo
    glew
    OpenGL::GL
    glfw
    imgui-glfw 
    imgui-opengl
)


###############
# Define a test
add_executable(register_test src/c++17/Counter/Counter_unittest.cpp src/c++17/Player/Player_unittest.cpp src/c++17/Space/Space_unittest.cpp src/c++17/Board/Board_unittest.cpp)
target_link_libraries(register_test gtest_main)

##################################
# Just make the test runnable with
#   $ make test
enable_testing()
add_test(NAME    register_test
         COMMAND register_test)

