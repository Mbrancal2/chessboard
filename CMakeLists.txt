cmake_minimum_required(VERSION 3.15)#PROJECT_VERSION_TWEAK 3.16)
project(chessgameproject  VERSION 1.0 DESCRIPTION "A simmple probably slow chess game")

enable_testing()


#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(chessgame src/chessgame.cpp src/interface.cpp src/board.cpp src/rules.cpp )
#target_compile_features(chessgame PRIVATE cxx_std_20)
target_include_directories(chessgame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include())



#add_executable(tests test/test.cpp)
#target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)