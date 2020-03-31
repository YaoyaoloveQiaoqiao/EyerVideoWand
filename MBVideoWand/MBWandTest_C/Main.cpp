#include <stdio.h>
#include <gtest/gtest.h>
#include <MBWand/MBWand.hpp>
#include <MBWand/InterfaceC.h>

TEST(MBWand, Version){
    char version[128];
    int ret = mb_c_get_version(version);
    ASSERT_EQ(ret, 0) << "mb_c_get_version fail";
    MBLog("MB Wand Version: %s\n", version);
}

TEST(MBWand, Demo){
    int width = 1280;
    int height = 720;
    int fps = 30;

    void * builder = mb_c_builder_init("c_interface_test.mp4", width, height, fps);

    void * video_track = mb_c_video_track_init();

    mb_c_builder_add_video_track(builder, video_track);





    mb_c_video_track_uninit(video_track);

    mb_c_builder_uninit(builder);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
