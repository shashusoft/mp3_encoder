cmake_minimum_required(VERSION 3.1)
project(mp3_encoder)

set(sources src/main.cpp src/wav.cpp src/logger.h src/thread_handler.cpp)
set(headers src/wav.h src/thread_handler.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
set(CMAKE_EXE_LINKER_FLAGS "-flto")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -flto" )

if(WIN32)
  include(pthreads-win32/pthreads-win32.cmake)
  list(APPEND sources pthreads-win32/pthreads-win32.cmake)
  set(libraries lame pthreads-win32)
  include_directories(${CMAKE_SOURCE_DIR}/lame/lame.h)
else()
 set(THREADS_PREFER_PTHREAD_FLAG ON)
 find_package(Threads REQUIRED)
 set(LAME_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/libmp3lame.a)
 set(LIBS ${LIBS} ${LAME_LIBRARIES} Threads::Threads stdc++fs)
 include_directories(${CMAKE_SOURCE_DIR}/lame/lame.h)
endif()

add_executable(${PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${LIBS})
#target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libmp3lame.a)

