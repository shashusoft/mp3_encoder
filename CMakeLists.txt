cmake_minimum_required(VERSION 3.1)
project(mp3_encoder)

set(sources src/main.cpp)
set(headers )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
set(CMAKE_EXE_LINKER_FLAGS "-flto")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -flto" )

find_package(Threads REQUIRED)
find_package(Lame REQUIRED)

set(LIBS ${LIBS} ${LAME_LIBRARIES} Threads::Threads stdc++fs)

include_directories(${LAME_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${sources} ${headers} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBS})


