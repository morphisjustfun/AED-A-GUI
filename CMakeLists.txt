cmake_minimum_required(VERSION 3.5)

project(GUIRR VERSION 0.1 LANGUAGES CXX)

include(FetchContent)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
  json
  GIT_REPOSITORY
    https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        datawindow.h datawindow.cpp datawindow.ui
            Graph/Algorithms/astar.h
            Graph/Algorithms/bfs.h
            Graph/Algorithms/dfs.h
            Graph/Algorithms/dijkstra.h
            Graph/Algorithms/kruskal.h
            Graph/Algorithms/bellmanFord.h
            Graph/Algorithms/prim.h
            Graph/Algorithms/astar.cpp
            Graph/Algorithms/bfs.cpp
            Graph/Algorithms/dfs.cpp
            Graph/Algorithms/dijkstra.cpp
            Graph/Algorithms/kruskal.cpp
            Graph/Algorithms/bellmanFord.cpp
            Graph/Algorithms/prim.cpp
            Graph/DirectedGraph.h
            Graph/graph.h
            Graph/UndirectedGraph.h
            Graph/DirectedGraph.cpp
            Graph/graph.cpp
            Graph/UndirectedGraph.cpp
            Parser/Data/airports.json
            Parser/Data/desktop.ini
            Parser/Data/pe.json
            Parser/desktop.ini
            Parser/parser.h
            Parser/parser.cpp
            Dset/ds.h
            Dset/dsarray.h
            Dset/ds.cpp
            Dset/dsarray.cpp
            Graph/Algorithms/FloydWarshall.h
            Graph/Algorithms/GreedyBfs.h
            Graph/Algorithms/FloydWarshall.cpp
            Graph/Algorithms/GreedyBfs.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GUIRR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(GUIRR SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(GUIRR
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GUIRR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets nlohmann_json::nlohmann_json stdc++fs)

set_target_properties(GUIRR PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GUIRR)
endif()
