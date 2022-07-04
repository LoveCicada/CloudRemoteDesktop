
cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} VERSION 1.0.0)

message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS QT_DIR=$ENV{QT_DIR})
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS $ENV{QT_DIR} PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if (QT_VERSION)
    message(STATUS "Qt version is ${QT_VERSION}")
    string(REPLACE "." ";" QT_VERSION_LIST ${QT_VERSION})
    list(GET QT_VERSION_LIST 0 QT_VERSION_MAJOR)
    set(Qt "Qt${QT_VERSION_MAJOR}")
else()
    message(FATAL_ERROR "Con not find valid qt version!")
endif()

list(PREPEND CMAKE_PREFIX_PATH $ENV{QT_DIR})
find_package(${Qt} COMPONENTS Widgets Core Gui Network REQUIRED)

macro(find_src SRC_FILES DIR)
    set (FILTER *.cpp *.h *.c *.cc *.hpp *.qrc)
    foreach(EXTR ${FILTER})
        file(GLOB_RECURSE FILES ${DIR}/${EXTR})
        list(APPEND ${SRC_FILES} ${FILES})
    endforeach() 
endmacro()

find_src(SRC_FILES ${CMAKE_SOURCE_DIR}/src)
foreach(FILE ${SRC_FILES})
    message("${FILE}")
endforeach() 

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_FILES})
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Qt}::Widgets
    ${Qt}::Core
    ${Qt}::Gui
    ${Qt}::Network
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if(DEPLOY_QT_RUNTIME)
    get_target_property(uic_location ${Qt}::uic IMPORTED_LOCATION)
    get_filename_component( _dir ${uic_location} DIRECTORY)
    set(deployqt "${_dir}/windeployqt.exe")
    if(NOT EXISTS ${deployqt})
        message(FATAL_ERROR "Failed to locate deployqt executable: [${deployqt}]")
    else()
        list(APPEND arg --no-translations)
        list(APPEND arg --pdb)
        list(APPEND arg --plugindir)
        list(APPEND arg $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins)
        list(APPEND arg $<TARGET_FILE:${PROJECT_NAME}>)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${deployqt} ${arg}
        )
    endif() 
endif(DEPLOY_QT_RUNTIME)