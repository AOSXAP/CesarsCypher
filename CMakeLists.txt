cmake_minimum_required (VERSION 3.11)
 
project(cesar_cypher LANGUAGES CXX VERSION 1.0.0)

file(COPY "text.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "distribution.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(cesar_cypher main.cpp cesar.cpp ui.cpp)
target_link_libraries(cesar_cypher -lmenu)
target_link_libraries(cesar_cypher -lncurses)



