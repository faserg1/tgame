file(GLOB_RECURSE TESTGAME_SOURCES *.cpp *.hpp *.h)
add_executable(tgame ${TESTGAME_SOURCES})

target_link_directories(tgame PRIVATE ${BEXT_SML_INCLUDE_DIRS})
target_link_libraries(tgame PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image)