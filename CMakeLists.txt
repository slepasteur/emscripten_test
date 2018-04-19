cmake_minimum_required(VERSION 3.5)

project(em_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-undefined-internal -Wno-missing-prototypes -Wno-undefined-func-template")

# Emscripten configuration.
set(EM_SDL_FLAGS " -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")
set(EM_FLAGS "${EM_SDL_FLAGS} -s EXPORTED_FUNCTIONS='[\"_em_main\"]' ")
set(EM_FLAGS "${EM_FLAGS} -s \"EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']\" ")
#set(EM_FLAGS "${EM_FLAGS} --preload-file assets ")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EM_FLAGS}")

set(SOURCE_FILES
  test.cpp
  drawable.cpp
)

add_executable(em_test ${SOURCE_FILES})
