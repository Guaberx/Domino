cmake_minimum_required(VERSION 3.5)###################
project(Proyecto)###################


set(SOURCE_FILES main.cpp)###################

SET(FLAGS "-std=c++11 -O3")

SET(SDL_INCLUDE ${CMAKE_SOURCE_DIR}/SDL2-2.0.4/i686-w64-mingw32/include/SDL2)
SET(SDL_LIBS ${CMAKE_SOURCE_DIR}/SDL2-2.0.4/i686-w64-mingw32/lib)

SET(SDL_IMAGE_INCLUDE ${CMAKE_SOURCE_DIR}/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2)
SET(SDL_IMAGE_LIBS ${CMAKE_SOURCE_DIR}/SDL2_image-2.0.1/i686-w64-mingw32/lib)

SET(SDL_MIXER_INCLUDE ${CMAKE_SOURCE_DIR}/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2)
SET(SDL_MIXER_LIBS ${CMAKE_SOURCE_DIR}/SDL2_mixer-2.0.1/i686-w64-mingw32/lib)

SET(EXTRA_LIBRARIES mingw32 SDL2main SDL2 SDL2_image SDL2_mixer)
SET(INCLUDE_ALL ${SDL_INCLUDE} ${SDL_IMAGE_INCLUDE} ${SDL_MIXER_INCLUDE})
SET(LIBS_ALL ${SDL_LIBS} ${SDL_IMAGE_LIBS} ${SDL_MIXER_LIBS})

INCLUDE_DIRECTORIES(${INCLUDE_ALL})
LINK_DIRECTORIES(${LIBS_ALL})

add_executable(Proyecto main.cpp SERVER.h SERVER.cpp CLIENT.h CLIENT.cpp Domino.h Player.h Board.h Game.h Board.cpp Domino.cpp)####################

TARGET_LINK_LIBRARIES(Proyecto ${EXTRA_LIBRARIES})

if(WIN32)
    target_link_libraries(Proyecto wsock32 ws2_32)
endif()