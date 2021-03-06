cmake_minimum_required(VERSION 3.20)
project(Editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:\\qttt\\5.12.11\\msvc2017\\")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(SOURCES
        GlobalShit.h
        MainWindow.h
        MainWindow.cpp
        ULine.h
        ULine.cpp
        DrawManager.h
        DrawManager.cpp
        Mode.h
        Mode.cpp
        LineMode.h
        LineMode.cpp
        EditorAction.h
        EditorAction.cpp
        ActionGraphicsScene.h
        ActionGraphicsScene.cpp
        SecondOrderMode.h
        SecondOrderMode.cpp
        USecondOrder.h
        USecondOrder.cpp
        Curve.h
        Curve.cpp
        CurveMode.h
        CurveMode.cpp
        Matrix.h
        Matrix.cpp
        FreeMode.h
        FreeMode.cpp)

list(TRANSFORM SOURCES PREPEND "src/")


add_executable(Editor main.cpp ${SOURCES} ${QT_TEST_UI_HEADERS})
target_link_libraries(Editor
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
