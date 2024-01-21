cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(TradeSystem LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/ProgramFiles/Qt/Qt5.2.0/5.2.0/msvc2012") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(INCS ${CMAKE_CURRENT_SOURCE_DIR}/api
         ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml)        
SET(LNKS ${CMAKE_CURRENT_SOURCE_DIR}/api)
         
INCLUDE_DIRECTORIES(${INCS})
LINK_DIRECTORIES(${LNKS})

find_package(Qt5 COMPONENTS Core Quick Widgets Sql REQUIRED) # Qt COMPONENTS

FILE(GLOB SRC_LISTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml/*.cpp)
# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement 
    ${SRC_LISTS}
) 
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Sql thostmduserapi_se thosttraderapi_se) # Qt5 Shared Library