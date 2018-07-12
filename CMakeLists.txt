cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(em_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")



# Immer library path
set(IMMER_LIBRARY_PATH "" CACHE FILEPATH "Path to immer library.")

if(NOT EXISTS ${IMMER_LIBRARY_PATH}/immer/vector.hpp)
  message(SEND_ERROR "Can't find immer/vector.hpp in ${IMMER_LIBRARY_PATH}")
endif()

include_directories(${IMMER_LIBRARY_PATH})
include_directories(include)

set(SOURCE_FILES
  src/main.cpp
  src/draw/drawable.cpp
  src/draw/line.cpp
  src/draw/rectangle.cpp
  src/action.cpp
  src/entity.cpp
  src/model.cpp
  src/event_loop.cpp
  src/update.cpp
)

add_executable(em_test ${SOURCE_FILES})

if (EMSCRIPTEN)
# Emscripten configuration.
set(EM_SDL_FLAGS " -s USE_SDL=2")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EM_SDL_FLAGS}")

# Compile as HTML
set(EM_LINKER_FLAGS " --shell-file ${PROJECT_SOURCE_DIR}/resources/em_test_shell.html --emrun")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EM_LINKER_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
# Native code configuration.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(em_test ${SDL2_LIBRARIES})
endif()

