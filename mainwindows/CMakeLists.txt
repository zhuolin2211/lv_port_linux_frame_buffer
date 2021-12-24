cmake_minimum_required(VERSION 3.5)

project(mainwindows LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#resources

aux_source_directory(resources/font  FONT_SRC)
aux_source_directory(resources/img  IMG_SRC)

add_subdirectory(../lv_drivers  LVGL_DRIVERS)
add_subdirectory(../lvgl  LVGL)
add_subdirectory(../lv_demos  LVGL_DEMOS)

include_directories(.)
include_directories(../)

set(MAIN_WINDOWS_SRC main.cpp main_windows.cpp menu_windows.cpp)

add_subdirectory(./json)
add_subdirectory(./http)
include_directories(./json/include)
include_directories(./http)

aux_source_directory(./NetworkTask  NETWORKTASK)
include_directories(./NetworkTask)

aux_source_directory(./playaudio PLAYAUDIO)
include_directories(./playaudio)
include_directories(./playaudio/rtrudio)
link_directories(./playaudio/rtrudio)
link_libraries(/home/sun/project/desktop_xiaofu/desktop_xiaofu/lv_port_linux_frame_buffer/mainwindows/playaudio/rtrudio/librtaudio.so.6.0.1)

aux_source_directory(./musicplayer  MUSICPLAYER)
include_directories(./musicplayer)



add_executable(main_windows ${FONT_SRC} ${IMG_SRC} ${MAIN_WINDOWS_SRC}
                            ${NETWORKTASK}
                            ${PLAYAUDIO}
                            ${MUSICPLAYER})


target_link_libraries(main_windows lv_drivers)
target_link_libraries(main_windows lvgl)
target_link_libraries(main_windows lv_examples)
target_link_libraries(main_windows json)
target_link_libraries(main_windows http)
