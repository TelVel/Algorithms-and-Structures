cmake_minimum_required(VERSION 3.24)
project(Graph_RGR)

set(CMAKE_CXX_STANDARD 17)

add_executable(Graph_RGR src/main.cpp src/SimpleGraph.cpp src/SimpleGraph.h
        src/elements/Edge.cpp src/elements/Edge.h
        src/elements/Vertex.cpp src/elements/Vertex.h
        src/iterators/EdgeIterator.cpp src/iterators/EdgeIterator.h
        src/iterators/VertexIterator.cpp src/iterators/VertexIterator.h
        src/forms/LGraph.cpp src/forms/LGraph.h
        src/forms/MGraph.cpp src/forms/MGraph.h
        src/forms/GraphForm.cpp src/forms/GraphForm.h
        src/Task2.cpp src/Task2.h
        src/Task3.cpp src/Task3.h
        src/menu/menu.cpp src/menu/menu.h)