cmake_minimum_required(VERSION 3.5)

project(mainwindows LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#resources

aux_source_directory(resources/font  FONT_SRC)
aux_source_directory(resources/img  IMG_SRC)

add_subdirectory(../lv_drivers  LVGL_DRIVERS)
add_subdirectory(../lvgl  LVGL)

include_directories(.)
include_directories(../)

set(MAIN_WINDOWS_SRC main.cpp main_windows.cpp)

add_subdirectory(./json)
add_subdirectory(./http)
include_directories(./json/include)
include_directories(./http)

aux_source_directory(./NetworkTask  NETWORKTASK)
include_directories(./NetworkTask)


add_executable(main_windows ${FONT_SRC} ${IMG_SRC} ${MAIN_WINDOWS_SRC}
                            ${NETWORKTASK})


target_link_libraries(main_windows lv_drivers)
target_link_libraries(main_windows lvgl)
target_link_libraries(main_windows json)
target_link_libraries(main_windows http)
