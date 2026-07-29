cmake_minimum_required(VERSION 3.16)
project(drawdemo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup()

qt_add_executable(drawdemo
    main.cpp
    DrawArea.h
    DrawArea.cpp
)

qt_add_qml_module(drawdemo
    URI DrawDemo
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(drawdemo PRIVATE Qt6::Quick)