cmake_minimum_required (VERSION 3.6)

add_executable(sokohard filewriter.cpp
                        filewriter.h
                        inputparser.cpp
                        inputparser.h
                        levelgenerator.cpp
                        levelgenerator.h
                        main.cpp
                        map_elements.h
                        map.cpp
                        map.h
                        mapgenerator.cpp
                        mapgenerator.h
                        pattern.cpp
                        pattern.h
                        patterns_list.h
                        position.h
                        positionselector.cpp
                        positionselector.h
                        solutionhandler.cpp
                        solutionhandler.h
                        state.cpp
                        state.h
                        util.cpp
                        util.h
                    )
include_directories("${PROJECT_SOURCE_DIR}")
