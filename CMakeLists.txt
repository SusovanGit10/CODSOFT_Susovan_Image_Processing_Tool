cmake_minimum_required(VERSION 3.16)

project(Susovan_Image_Editor VERSION 0.1 LANGUAGES CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ IMPORTANT: Point to vc16 (MSVC2019)
set(OpenCV_DIR "C:/OpenCV/build/x64/vc16/lib")

# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# OpenCV
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    imageview.cpp
    imageview.h
)

# Create executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Susovan_Image_Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        imageview.h
    )
else()
    add_executable(Susovan_Image_Editor
        ${PROJECT_SOURCES}
    )
endif()

# ✅ Link libraries (AUTO)
target_link_libraries(Susovan_Image_Editor PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
)

# Windows bundle settings
set_target_properties(Susovan_Image_Editor PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Susovan_Image_Editor)
endif()