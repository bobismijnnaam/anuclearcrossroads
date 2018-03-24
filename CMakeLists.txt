cmake_minimum_required(VERSION 3.2)
project(LudumDare32)

add_definitions(-std=c++11 -g -DNNB_LOGLVL_RELEASE -DPLSREBUILD) # -mwindows -static-libstdc++ -static-libgcc
include_directories("${PROJECT_SOURCE_DIR}/headers")
include_directories("${PROJECT_SOURCE_DIR}/nutsnbolts/headers")
link_directories("${PROJECT_SOURCE_DIR}/nutsnbolts/build")

add_subdirectory(sources)

add_executable(ld32
	${SOURCES}
)

target_link_libraries(ld32 nutsnbolts SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2 png jpeg z)

IF (WIN32)
    
ENDIF()

if (UNIX)
    
endif (UNIX)

