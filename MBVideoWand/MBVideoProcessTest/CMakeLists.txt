add_executable(
    MBVideoProcessTest
    Test.cpp

    MBVPAudioResTest.hpp
    MBVPAudioTrackTest.hpp
    MBVPReadImageTest.h 
    MBVPVideoText.h
)

include_directories (../)

target_link_libraries (MBVideoProcessTest MBVideoProcess)
target_link_libraries (MBVideoProcessTest gtest)


target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/MBLib/lib/libMBGL.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/MBLib/lib/libMBType.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/MBLib/lib/libMBYUV.a)

target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/freetype_install/lib/libfreetype.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/libpng_install/lib/libpng.a)
target_link_libraries (MBVideoProcessTest ${CMAKE_SOURCE_DIR}/../../Lib/libyuv_install/lib/libyuv.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (MBVideoProcessTest dl)
    target_link_libraries (MBVideoProcessTest z)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


INSTALL(
    TARGETS MBVideoProcessTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )
