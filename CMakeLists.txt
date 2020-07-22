cmake_minimum_required(VERSION 3.1)
project(mp3_encoder)

set(sources src/thread_handler.cpp src/main.cpp src/wav.cpp)
set(headers src/logger.h src/thread_handler.h src/wav.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
set(CMAKE_EXE_LINKER_FLAGS "-flto")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -flto" )


if(WIN32)
  include(pthreads-win32/pthreads-win32.cmake)
  list(APPEND sources pthreads-win32/pthreads-win32.cmake)
  set(sources ${sources} lame/lame.cmake)	
  include(lame/lame.cmake)

  set(LIBS ${LIBS} LAME_LIBRARIES pthreads-win32)
  include_directories(${CMAKE_SOURCE_DIR}/include/)

  if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
    # Default debug flags are OK
    set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} some other flags")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()

else()
 set(THREADS_PREFER_PTHREAD_FLAG ON)
 find_package(Threads REQUIRED)
 set(LAME_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/libmp3lame.a)
 set(LIBS ${LIBS} ${LAME_LIBRARIES} Threads::Threads stdc++fs)
 include_directories(${CMAKE_SOURCE_DIR}/include/)
endif()

add_executable(${PROJECT_NAME} ${sources} ${headers} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBS})
#target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libmp3lame.a)

if(WIN32)
  get_property(pthreads-win32-location TARGET pthreads-win32 PROPERTY LOCATION)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${pthreads-win32-location}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()