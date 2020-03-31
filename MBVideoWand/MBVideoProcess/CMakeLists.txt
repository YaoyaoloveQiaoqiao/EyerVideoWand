include_directories (../)
include_directories (./)

add_library(
    MBVideoProcess
    MBVideoProcess.hpp
    MBVPAudioTrack.cpp
    MBVPResource.cpp
    MBVPVideoTrack.cpp
    MBVPVideoRes.cpp
    MBVPVideoImage.cpp
)

target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/MBLib/lib/libMBAV.a)
target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/MBLib/lib/libMBCore.a)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/include)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (MBVideoProcess dl)
    target_link_libraries (MBVideoProcess z)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (MBVideoProcess z)
    target_link_libraries (MBVideoProcess bz2)
    target_link_libraries (MBVideoProcess ws2_32)
    target_link_libraries (MBVideoProcess Secur32)
    target_link_libraries (MBVideoProcess lzma)
    target_link_libraries (MBVideoProcess iconv)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (MBVideoProcess bz2)
    target_link_libraries (MBVideoProcess z)
    target_link_libraries (MBVideoProcess lzma)
    target_link_libraries (MBVideoProcess iconv)


    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.dylib)
    target_link_libraries (MBVideoProcess ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)
    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

INSTALL(
    TARGETS MBVideoProcess
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

