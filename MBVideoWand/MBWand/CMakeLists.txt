include_directories (../)
include_directories (./)

add_library(
        MBWand
        SHARED

        MBWand.cpp
        MBWandResource.cpp
        MBWandVideoResource.cpp
        MBWandAudioResource.cpp
        MBWandBuilder.cpp
        MBVideoTrack.cpp
        MBVideoLayout.cpp

        MBVideoPanel.cpp
        InterfaceC.cpp
        InterfaceCSharp.cpp
        MBVideoDecoderLine.cpp
        MBAudioTrack.cpp
        MBAudioLayer.cpp
        MBAudioFragment.cpp
        MBWandDebug.cpp
        MBVideoFragmentText.cpp
        MBVideoFragmentVideo.cpp
        MBVideoFragment.cpp
        MBTransKey.cpp
        MBFilterKey.cpp
        )

target_link_libraries (MBWand MBCore)
target_link_libraries (MBWand MBAV)
target_link_libraries (MBWand MBGLWindow)
target_link_libraries (MBWand MBGL)
target_link_libraries (MBWand MBGLCustomComponent)
target_link_libraries (MBWand MBYUV)
target_link_libraries (MBWand MBGPUDomino)
target_link_libraries (MBWand MBGLAD)
target_link_libraries (MBWand MBType)
target_link_libraries (MBWand MBGLShader)

ADD_DEFINITIONS(-D EYER_DEBUG)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (MBWand avformat)
    target_link_libraries (MBWand avdevice)
    target_link_libraries (MBWand avcodec)
    target_link_libraries (MBWand avutil)
    target_link_libraries (MBWand avfilter)
    target_link_libraries (MBWand swresample)
    target_link_libraries (MBWand swscale)

    target_link_libraries (MBWand x264)

    target_link_libraries (MBWand glfw3)
    target_link_libraries (MBWand X11)

    target_link_libraries (MBWand libyuv.a)
    target_link_libraries (MBWand libfreetype.a)
    target_link_libraries (MBWand png)
    target_link_libraries (MBWand harfbuzz)
    target_link_libraries (MBWand bz2)
    target_link_libraries (MBWand lzma)

    target_link_libraries (MBWand dl)
    target_link_libraries (MBWand z.a)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (MBWand avformat)
    target_link_libraries (MBWand avdevice)
    target_link_libraries (MBWand avcodec)
    target_link_libraries (MBWand avutil)
    target_link_libraries (MBWand avfilter)
    target_link_libraries (MBWand swresample)
    target_link_libraries (MBWand swscale)

    target_link_libraries (MBWand libglfw3.a)

    target_link_libraries (MBWand libyuv.a)
    target_link_libraries (MBWand libfreetype.a)

    target_link_libraries (MBWand z)
    target_link_libraries (MBWand bz2)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (MBWand avformat)
    target_link_libraries (MBWand avdevice)
    target_link_libraries (MBWand avcodec)
    target_link_libraries (MBWand avutil)
    target_link_libraries (MBWand avfilter)
    target_link_libraries (MBWand swresample)
    target_link_libraries (MBWand swscale)

    target_link_libraries (MBWand dl)
    target_link_libraries (MBWand z)

    target_link_libraries (MBWand x264)

    target_link_libraries (MBWand glfw3)

    target_link_libraries (MBWand libyuv.a)
    target_link_libraries (MBWand libfreetype.a)
    target_link_libraries (MBWand png)
    target_link_libraries (MBWand bz2)
    target_link_libraries (MBWand iconv)
    target_link_libraries (MBWand lzma)

    macro(ADD_FRAMEWORK appname fwname) 
        find_library(FRAMEWORK_${fwname} NAMES ${fwname} PATHS ${CMAKE_OSX_SYSROOT}/System/Library PATH_SUFFIXES Frameworks NO_DEFAULT_PATH) 
        if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND) 
            MESSAGE(ERROR ": Framework ${fwname} not found") 
        else() 
            TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}.tbd") 
            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}") 
        endif() 
    endmacro(ADD_FRAMEWORK)

    add_framework(MBWand AudioToolbox)
    add_framework(MBWand IOKit)
    add_framework(MBWand CoreGraphics)
    add_framework(MBWand CoreMedia)
    add_framework(MBWand Cocoa)
    add_framework(MBWand VideoToolbox)
    add_framework(MBWand AVFoundation)
    add_framework(MBWand Security)
    add_framework(MBWand CoreFoundation)
    add_framework(MBWand CoreVideo)
    add_framework(MBWand OpenGL)
    add_framework(MBWand AppKit)
    add_framework(MBWand CoreImage)
    add_framework(MBWand VideoDecodeAcceleration)

    set(CMAKE_EXE_LINKER_FLAGS
        "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
        TARGETS MBWand
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

