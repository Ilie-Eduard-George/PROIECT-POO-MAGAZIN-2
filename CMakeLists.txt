cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT_NAME "oop")
project(${MAIN_PROJECT_NAME} LANGUAGES CXX)

# Use C++17 for compatibility with assignment requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include helper cmake files if you still need them
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/Options.cmake")
  include(cmake/Options.cmake)
endif()
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/CompilerFlags.cmake")
  include(cmake/CompilerFlags.cmake)
endif()
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/CopyHelper.cmake")
  include(cmake/CopyHelper.cmake)
endif()

# add include directory so headers are found
target_include_directories(${MAIN_PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include)
# or globally:
include_directories(${CMAKE_SOURCE_DIR}/include)

# collect all .cpp sources from src/
file(GLOB_RECURSE PROJECT_SOURCES
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# if you still have a top-level main.cpp, either move it to src/ or add it explicitly:
# list(APPEND PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")

add_executable(${MAIN_PROJECT_NAME} ${PROJECT_SOURCES})

# optional: set compiler flags helper if present
if(COMMAND set_compiler_flags)
  set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_PROJECT_NAME})
endif()

# install and copy helpers (keep if CopyHelper.cmake exists)
if(COMMAND install)
  install(TARGETS ${MAIN_PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
  if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
  endif()
endif()

# copy extra files (if CopyHelper.cmake defines copy_files)
if(COMMAND copy_files)
  copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_PROJECT_NAME})
endif()
