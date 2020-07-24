cmake_minimum_required (VERSION 3.10)

project (Ludo)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
# Main Include
add_executable(Ludo src/c++17/Counter/Counter.cpp src/c++17/Player/Player.cpp src/c++17/Space/Space.cpp src/c++17/Board/Board.cpp  src/c++17/main.cpp)

################
# Define a test
add_executable(register_test src/c++17/Counter/Counter_unittest.cpp src/c++17/Player/Player_unittest.cpp src/c++17/Space/Space_unittest.cpp src/c++17/Board/Board_unittest.cpp)
target_link_libraries(register_test gtest_main)

##################################
# Just make the test runnable with
#   $ make test
enable_testing()
add_test(NAME    register_test
         COMMAND register_test)

