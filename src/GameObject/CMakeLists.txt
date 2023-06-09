cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.hpp
  GameObject.cpp
)

target_link_libraries(
  GameObject
  Framework
  GameWorld
)

target_link_libraries(
  GameObject
  Plant
)

target_link_libraries(
  GameObject
  Seed
)

target_link_libraries(
  GameObject
  Zombie
)

target_include_directories(
  GameObject
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Plant/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Seed/
  ${CMAKE_SOURCE_DIR}/src/GameObject/Zombie/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
)
