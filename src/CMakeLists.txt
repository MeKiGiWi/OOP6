
add_library(livers  npc.cpp orc.cpp squirrel.cpp bear.cpp)
add_executable(main main.cpp)
target_link_libraries(main livers)
