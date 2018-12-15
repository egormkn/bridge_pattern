cmake_minimum_required(VERSION 3.10)
project(bridge_pattern)

set(CMAKE_CXX_STANDARD 14)

add_executable(bridge_pattern
        main.cpp
        api/DrawingApi.h
        api/SFMLDrawingApi.cpp
        api/SFMLDrawingApi.h
        api/SDLDrawingApi.cpp
        api/SDLDrawingApi.h graph/Graph.cpp graph/Graph.h api/DrawingApi.cpp graph/MatrixGraph.cpp graph/MatrixGraph.h graph/MatrixGraph.cpp graph/MatrixGraph.h graph/EdgeListGraph.cpp graph/EdgeListGraph.h)

find_package(SFML CONFIG REQUIRED COMPONENTS graphics window system)
target_link_libraries(bridge_pattern PRIVATE sfml-graphics sfml-system sfml-window X11 FLAC UDev OpenAL GL)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(bridge_pattern PRIVATE SDL2::SDL2main SDL2::SDL2-static)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(bridge_pattern PRIVATE Boost::program_options)