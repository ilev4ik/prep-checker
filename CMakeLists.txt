cmake_minimum_required(VERSION 3.1.0)

project(prep-checker)
cmake_policy(SET CMP0076 NEW)

# project settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS})
set(CXX_STANDARD 11)
set(PROJECT_EXECUTABLE_NAME ${PROJECT_NAME})
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_SOURCE_FILES 
    ${SOURCE_DIR}/mainwindow.cpp
    ${SOURCE_DIR}/object_entry_window.cpp
    ${SOURCE_DIR}/test_meta_window.cpp
    ${SOURCE_DIR}/test_viewer_window.cpp
    ${SOURCE_DIR}/tests_window.cpp
)

include_directories(src)

find_package(Boost 1.73 REQUIRED COMPONENTS log)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# testing settings
#enable_testing()
#set(GTEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/googletest/googletest)
#add_subdirectory(${GTEST_SOURCE_DIR})
#add_subdirectory(test)

# qt
find_package(Qt5 COMPONENTS Core Widgets Xml XmlPatterns REQUIRED)
include_directories(
    ${Qt5Core_INCLUDES} 
    ${Qt5Widgets_INCLUDES}
    ${Qt5Xml_INCLUDE_DIRS}
    ${Qt5XmlPatterns_INCLUDE_DIRS}
    )
add_definitions(${Qt5Widgets_DEFINITIONS} ${DEFINITIONS})

# target compilation
set(TARGET_NAME ${PROJECT_EXECUTABLE_NAME}_${CMAKE_BUILD_TYPE})
add_executable(${TARGET_NAME} src/main.cpp)
target_sources(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_FILES})
set_target_properties(${TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
)

target_link_libraries(${TARGET_NAME} 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::XmlPatterns 
    Qt5::Xml 
    ${Boost_LOG_LIBRARY}
)

# qt dlls
if (WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe)

    set(QT5_WINDEPLOYQT_BUILDTYPE_OPTION "")
    string(TOLOWER ${CMAKE_BUILD_TYPE} QT5_WINDEPLOYQT_BUILDTYPE_OPTION)
    string(PREPEND QT5_WINDEPLOYQT_BUILDTYPE_OPTION "--")
    
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
       COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} ${QT5_WINDEPLOYQT_BUILDTYPE_OPTION} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endif(WIN32)