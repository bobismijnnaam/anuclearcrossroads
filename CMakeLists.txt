cmake_minimum_required(VERSION 3.2)
project(LudumDare32)

include_directories("${PROJECT_SOURCE_DIR}/headers")
include_directories("${PROJECT_SOURCE_DIR}/nutsnbolts/headers")

IF (WIN32)
	#############
	## PNG LIB ##
	#############

    link_directories(
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/build/Release"
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2-2.0.8/lib/x86"
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_image-2.0.3/lib/x86"
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_mixer-2.0.2/lib/x86"
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_ttf-2.0.14/lib/x86"
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/"
    	)

    include_directories(
    	"${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2-2.0.8"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2-2.0.8/include"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_image-2.0.3"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_image-2.0.3/include"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_mixer-2.0.2"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_mixer-2.0.2/include"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_ttf-2.0.14"
        "${PROJECT_SOURCE_DIR}/nutsnbolts/lib/SDL2_ttf-2.0.14/include"
    	)

    add_definitions(/D__BASE_FILE__="lol_windows" /DNNB_LOGLVL_RELEASE /DPLSREBUILD /std:c++14)
ENDIF()

if (UNIX)
	add_definitions(-std=c++11 -g -DNNB_LOGLVL_RELEASE -DPLSREBUILD) # -mwindows -static-libstdc++ -static-libgcc
    link_directories("${PROJECT_SOURCE_DIR}/nutsnbolts/build")
endif (UNIX)

add_subdirectory(sources)

add_executable(ld32
	${SOURCES}
)

target_link_libraries(ld32 nutsnbolts SDL2_image SDL2_mixer SDL2_ttf SDL2main SDL2 png jpeg z)