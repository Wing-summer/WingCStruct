cmake_minimum_required(VERSION 3.16)

project(WingCStruct LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /utf-8")
    string(APPEND CMAKE_C_FLAGS " /utf-8")
endif()

option(TEST_MODE TRUE)

if(NOT EXISTS "${WINGHEX_SDK}")
    message(FATAL_ERROR "Please config the SDK Path - WINGHEX_SDK")
endif()

set(PLUGIN_INTERFACE_BASE_FOUND FALSE)
set(PLUGIN_INTERFACE_FOUND FALSE)
set(PLUGIN_SETPAGE_FOUND FALSE)
if(EXISTS "${WINGHEX_SDK}/iwingpluginbase.h")
    set(PLUGIN_INTERFACE_BASE_FOUND TRUE)
endif()
if(EXISTS "${WINGHEX_SDK}/iwingplugin.h")
    set(PLUGIN_INTERFACE_FOUND TRUE)
endif()
if(EXISTS "${WINGHEX_SDK}/settingpage.h")
    set(PLUGIN_SETPAGE_FOUND TRUE)
endif()
if(PLUGIN_INTERFACE_FOUND
   AND PLUGIN_INTERFACE_BASE_FOUND
   AND PLUGIN_SETPAGE_FOUND)
    message(STATUS "${WINGHEX_SDK} is valid SDK path")
else()
    message(FATAL_ERROR "Invalid SDK path!")
endif()

set(WINGHEX_SDK_HEADER
    "${WINGHEX_SDK}/iwingplugin.h" "${WINGHEX_SDK}/iwingpluginbase.h"
    "${WINGHEX_SDK}/settingpage.h")
include_directories(${WINGHEX_SDK})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES WingCStruct_zh_CN.ts)

set(TRANSLATION_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} EQUAL 5)
    qt5_create_translation(QM_FILES ${TRANSLATION_PATH} ${TS_FILES})
elseif(${QT_VERSION_MAJOR} EQUAL 6)
    qt6_create_translation(QM_FILES ${TRANSLATION_PATH} ${TS_FILES})
else()
    message(FATAL_ERROR "Unsupported QT version")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TranslationUtils.cmake)
add_plugin_translations_resource(QM_RES WingCStruct ${QM_FILES})

add_library(
    WingCStruct SHARED
    ${WINGHEX_SDK_HEADER}
    ${QM_FILES}
    ${QM_RES}
    wingcstruct.cpp
    wingcstruct.h
    WingCStruct.json
    defines.h
    ctypeparser.cpp
    ctypeparser.h)

set_target_properties(WingCStruct PROPERTIES SUFFIX ".wingplg")

if(TEST_MODE)
    if(NOT EXISTS "${WINGHEX_PATH}")
        message(
            FATAL_ERROR "Please config the WingHexExplorer2 Path - WINGHEX_PATH"
        )
    endif()
    set(WINGHEX_PLUGIN_PATH "${WINGHEX_PATH}/plugin")
    add_custom_command(
        TARGET WingCStruct
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${WINGHEX_PLUGIN_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:WingCStruct> ${WINGHEX_PLUGIN_PATH})
endif()

target_link_libraries(WingCStruct PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
