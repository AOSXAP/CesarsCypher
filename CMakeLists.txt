cmake_minimum_required (VERSION 3.11)
 
project(cesar_cypher LANGUAGES CXX VERSION 1.0.0)

include_directories("${CMAKE_SOURCE_DIR}/headers")


#helper files
file(COPY "helpers/text.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "helpers/distribution.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB cpp_files
     "src/*.cpp"
     "headers/*.h"
)

#cpp files
add_executable(cesar_cypher ${cpp_files})

#header files
include_directories(../headers)

#dynamically linked libs
target_link_libraries(cesar_cypher -lmenu)
target_link_libraries(cesar_cypher -lncurses)



