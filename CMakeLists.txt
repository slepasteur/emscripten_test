cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(em_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Emscripten configuration.
set(EM_SDL_FLAGS " -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")
set(EM_FLAGS "${EM_SDL_FLAGS} -s EXPORTED_FUNCTIONS='[\"_em_main\"]' ")
set(EM_FLAGS "${EM_FLAGS} -s \"EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']\" ")
#set(EM_FLAGS "${EM_FLAGS} --preload-file assets ")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EM_FLAGS}")

# Immer library path
set(IMMER_LIBRARY_PATH "" CACHE FILEPATH "Path to immer library.")

if(NOT EXISTS ${IMMER_LIBRARY_PATH}/immer/vector.hpp)
  message(SEND_ERROR "Can't find immer/vector.hpp in ${IMMER_LIBRARY_PATH}")
endif()

include_directories(${IMMER_LIBRARY_PATH})
include_directories(include)

set(SOURCE_FILES
  src/test.cpp
  src/drawable.cpp
  src/action.cpp
)

add_executable(em_test ${SOURCE_FILES})
