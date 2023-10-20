cmake_minimum_required(VERSION 3.18)

project(DST_Mod_Tool)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" "Release")
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP AutoGen) 

#set qt package path
set(Qt5_DIR "D:/3rd/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
set(Qt5_BIN "D:/3rd/Qt/5.15.2/msvc2019_64/bin")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#设置编译输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(DstModTool
  WIN32
  main.cpp
  mainwindow.h mainwindow.cpp
)

target_link_libraries(DstModTool Qt5::Widgets)

if(MSVC)
   set(runtime_path_env "PATH=$ENV{PATH};${Qt5_BIN}")
   set_target_properties(DstModTool PROPERTIES VS_DEBUGGER_ENVIRONMENT "${runtime_path_env}")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT DstModTool)

#install
set(install_bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/install)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ DESTINATION ${install_bin})
install(CODE "execute_process(COMMAND ${Qt5_BIN}/windeployqt.exe \"${install_bin}/DstModTool.exe\" -no-translations)")