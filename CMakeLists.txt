cmake_minimum_required(VERSION 3.10)
project(ChessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Add the include directory so compiler can find .hpp files
include_directories("${PROJECT_SOURCE_DIR}/include")

# 2) Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 3) Grab all .cpp files from src/ 
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 4) Create the executable
add_executable(chess_game ${SOURCES})

# 5) Link SFML libraries
target_link_libraries(chess_game sfml-graphics sfml-window sfml-system)
