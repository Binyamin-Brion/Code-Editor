cmake_minimum_required(VERSION 3.8)
project(PerformanceMonitor)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MOC_HEADERS MainWindow.h CounterSelection.h CompilerSelection.h)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.11.2\\5.11.2\\mingw53_32")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})

qt5_wrap_ui(UI_HEADERS mainwindow.ui CounterSelection.ui CompilerSelection.ui)

qt5_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h DirectoryView.cpp DirectoryView.h ParentChildTree.cpp ParentChildTree.h TestParentChildTree.cpp TestParentChildTree.h TestSuite.cpp TestSuite.h CodeViewer.cpp CodeViewer.h CodeHighlighter.cpp CodeHighlighter.h FileViewer.cpp FileViewer.h CounterWriter.cpp CounterWriter.h TestCounterWriter.cpp TestCounterWriter.h CounterList.cpp CounterList.h CounterSelection.cpp CounterSelection.h ScrollArea.cpp ScrollArea.h ScrollCommands.cpp ScrollCommands.h ScrollCommandValues.cpp ScrollCommandValues.h PerformanceGraph.cpp PerformanceGraph.h)

add_executable(PerformanceMonitor ${SOURCE_FILES})

target_link_libraries(PerformanceMonitor ${Qt5Widgets_LIBRARIES} ${Qt5Test_LIBRARIES} ${Qt5Charts_LIBRARIES})
