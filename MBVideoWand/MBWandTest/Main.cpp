#include <stdio.h>
#include <gtest/gtest.h>
#include <MBWand/MBWand.hpp>

TEST(MBVideoFragment, whiteBG){
    /*
    int fps = 30;

    MB::MBWandBuilder builder("./struct_builder_vidoe_mp4_png.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    // 视频
    MB::MBVideoTrack videoTrack;

    MB::MBVideoLayout layer1;
    layer1.SetFrame(0, fps * 15);

    MB::MBVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./white.jpg");
    videoFragment2.AddScaleKey(0.0, 1280, 720, 1.0);
    videoFragment2.AddScaleKey(5.0, 1280, 720, 1.0);

    MB::MBVideoFragmentVideo videoFragment4;
    videoFragment4.LoadVideoFile("./eggCooker.jpg");
    videoFragment4.AddScaleKey(0.0, 100, 100, 1.0);
    videoFragment4.AddScaleKey(5.0, 100, 100, 1.0);
    videoFragment4.AddTransKey(0.0, -400, 0,0);
    videoFragment4.AddTransKey(5.0, -400, 0,0);

    MB::MBVideoFragmentVideo videoFragment3;
    videoFragment3.LoadVideoFile("./qipao.mp4");
    videoFragment3.AddScaleKey(0.0, 400, 400, 1.0);
    videoFragment3.AddScaleKey(5.0, 400, 400, 1.0);

    MB::MBVideoFragmentVideo videoFragment5;
    videoFragment5.LoadVideoFile("./start.mp4");
    videoFragment5.AddScaleKey(0.0, 500, 500, 1.0);
    videoFragment5.AddScaleKey(5.0, 500, 500, 1.0);
    videoFragment5.AddTransKey(0.0, 500, 0,0);
    videoFragment5.AddTransKey(5.0, 500, 0,0);

    layer1.AddVideoFragment(&videoFragment2);
    layer1.AddVideoFragment(&videoFragment3);
    layer1.AddVideoFragment(&videoFragment4);
    layer1.AddVideoFragment(&videoFragment5);

    videoTrack.AddLayout(layer1);

    builder.AddVideoTrack(videoTrack);

    builder.Process();
    */
}
TEST(MBVideoFragmentText, GetLinearTrans){
    
    int fps = 30;

    MB::MBWandBuilder builder("./struct_builder_vidoe_mp4_png.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    // 视频
    MB::MBVideoTrack videoTrack;

    MB::MBVideoLayout layer1;
    layer1.SetFrame(0, fps * 5);
    
    MB::MBVideoFragmentText videoFragmentText;
    videoFragmentText.AddTransKey(0.0, 0.0, 0.0);
    videoFragmentText.AddTransKey(5.0, 300.0, 300.0);
    videoFragmentText.SetFontPath("./xiao_xiao_yuan_pin_ying.ttf");
    videoFragmentText.SetText("这里是测试字幕");
    videoFragmentText.SetSize(100.0f);
    videoFragmentText.SetColor(1.0, 1.0, 0.0);

    layer1.AddVideoFragment(&videoFragmentText);
    videoTrack.AddLayout(layer1);

    builder.AddVideoTrack(videoTrack);
    builder.Process();
    
}

TEST(MBVideoFragment, readpng){
    /*
    int fps = 30;

    MB::MBWandBuilder builder("./struct_builder_vidoe_mp4_png.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(fps);

    // 视频
    MB::MBVideoTrack videoTrack;

    MB::MBVideoLayout layer1;
    layer1.SetFrame(0, fps * 3);



    MB::MBVideoFragmentVideo fragment1;
    fragment1.LoadVideoFile("./white.jpg");

    fragment1.AddScaleKey(0.0, 1280, 720, 0.0);
    fragment1.AddScaleKey(0.0, 1280, 720, 0.0);

    MB::MBVideoFragmentVideo fragment2;
    fragment2.LoadVideoFile("./qipao.mp4");
    // fragment2.LoadVideoFile("./scoreChart.mp4");
    fragment2.AddScaleKey(0.0, 500, 500, 0.0);
    fragment2.AddScaleKey(0.0, 500, 500, 0.0);
    layer1.AddVideoFragment(&fragment1);
    layer1.AddVideoFragment(&fragment2);
    videoTrack.AddLayout(layer1);

    

    builder.AddVideoTrack(videoTrack);

    builder.Process();
    */
}

TEST(MBWand, MB_Decoder_Line){
    /*
    MB::MBVideoDecoderLine decoderLine("./M_1280_720.mp4", 20.0);

    for(double ts = 20.0; ts < 40.0; ts += 0.01){
        MB::MBAVFrame frame;
        decoderLine.GetFrame(frame, ts);
    }
     */
}

TEST(MBWand, MBWandRes_Base){

}

TEST(MBVideoTrack, MBWandRes_Base){
    /*
    MB::MBWandBuilder builder("./struct_builder_mp4.mp4");

    MB::MBVideoTrack videoTrack;

    for(int i=0;i<1000;i++){
        MB::MBVideoLayout layout;
        layout.SetFrame(i, i + 1000);

        MB::MBVideoFragment videoFragment;
        videoFragment.SetFrameIndex(i, i + 1000);
        videoFragment.SetFrameTime(0.0, 10.0);

        layout.AddVideoFragment(videoFragment);

        videoTrack.AddLayout(layout);
    }

    int frameCount = videoTrack.GetFrameCount();
    ASSERT_EQ(frameCount, 999 + 1000) << "Get Frame Count Error!!!!";

    builder.AddVideoTrack(videoTrack);
     */
}

TEST(MBVideoBuild, MBVideoBuild_Test){
    /*
    int fps = 30;

    MB::MBWandBuilder builder("./struct_builder_vidoe_mp4.mp4");
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    MB::MBVideoTrack videoTrack;

    MB::MBVideoLayout layer1;
    layer1.SetFrame(0, fps * 5);

    MB::MBVideoLayout layer2;
    layer2.SetFrame(fps * 5, fps * 10);

    MB::MBVideoLayout layer3;
    layer3.SetFrame(fps * 10, fps * 15);

    MB::MBVideoLayout layer4;
    layer4.SetFrame(fps * 15, fps * 20);

    MB::MBVideoLayout layer5;
    layer5.SetFrame(fps * 20, fps * 25);

    MB::MBVideoFragmentVideo videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    videoFragment.AddTransKey(0.0, 5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.1, -5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.2, 3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.3, -3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.4, 2.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.5, 0.0, 0.0, 0.0);

    videoFragment.AddScaleKey(0.0, 1920.0, 1080.0, 0.0);
    videoFragment.AddScaleKey(5.0, 1920.0 / 2, 1080.0 / 2, 0.0);

    videoFragment.Print();

    MB::MBVideoFragmentVideo videoFragment2;
    videoFragment2.LoadVideoFile("./demo.mp4");
    videoFragment2.AddTransKey(0.0, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(0.1, -30.0, -30.0, 0.0);
    videoFragment2.AddTransKey(0.2, 30.0, 30.0, 0.0);
    videoFragment2.AddTransKey(0.3, -20.0, -20.0, 0.0);
    videoFragment2.AddTransKey(0.4, 20.0, 20.0, 0.0);
    videoFragment2.AddTransKey(0.5, 10.0, 10.0, 0.0);
    videoFragment2.AddTransKey(0.6, 0.0, 0.0, 0.0);


    videoFragment2.AddTransKey(2.1, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(2.2, 0.0, 20.0, 0.0);
    videoFragment2.AddTransKey(2.3, 0.0, -20.0, 0.0);
    videoFragment2.AddTransKey(2.4, 0.0, 10.0, 0.0);
    videoFragment2.AddTransKey(2.5, 0.0, -10.0, 0.0);
    videoFragment2.AddTransKey(2.6, 0.0, 6.0, 0.0);
    videoFragment2.AddTransKey(2.7, 0.0, 0.0, 0.0);

    videoFragment2.AddScaleKey(0.0, 1920.0 , 1080.0, 0.0);
    videoFragment2.AddScaleKey(5.0, 1920.0, 1080.0, 0.0);

    videoFragment2.Print();


    MB::MBVideoFragmentText videoFragmentText;
    videoFragmentText.SetFontPath("./xiao_xiao_yuan_pin_ying.ttf");
    videoFragmentText.SetText("这里是测试字幕");
    videoFragmentText.SetSize(100.0f);
    videoFragmentText.SetColor(1.0, 1.0, 0.0);
    int width = videoFragmentText.GetTextWidth();
    MBLog("Text Width: %d\n", width);
    videoFragmentText.SetPos(1920 / 2.0 - width / 2.0, 400.0f);

    videoFragment.AddFilterKey(0.0, (int)MB::MBVideoFilterType::ZOOM_BLUR, 15);
    videoFragment.AddFilterKey(1.5, (int)MB::MBVideoFilterType::ZOOM_BLUR, 0);

    layer1.AddVideoFragment(&videoFragment);
    layer1.AddVideoFragment(&videoFragmentText);
    layer2.AddVideoFragment(&videoFragment2);

    MB::MBVideoFragmentVideo videoFragmentImage;
    videoFragmentImage.LoadVideoFile("./2.jpg");
    videoFragmentImage.AddScaleKey(0.0, 960.0, 540.0, 0.0);
    videoFragmentImage.AddScaleKey(5.0, 1460.0, 840.0, 0.0);

    layer3.AddVideoFragment(&videoFragmentImage);

    MB::MBVideoFragmentVideo videoFragmentImage2;
    videoFragmentImage2.LoadVideoFile("./4.jpg");
    videoFragmentImage2.AddScaleKey(0.0, 1460.0, 840.0, 0.0);
    videoFragmentImage2.AddScaleKey(5.0, 960.0, 540.0, 0.0);

    layer4.AddVideoFragment(&videoFragmentImage2);


    MB::MBVideoFragmentVideo videoFragmentImage3;
    videoFragmentImage3.LoadVideoFile("./1.jpg");
    videoFragmentImage3.AddScaleKey(0.0, 200.0, 200.0, 0.0);
    videoFragmentImage3.AddScaleKey(5.0, 200.0, 200.0, 0.0);

    layer5.AddVideoFragment(&videoFragmentImage3);

    videoTrack.AddLayer(layer1);
    // videoTrack.AddLayer(layer2);
    // videoTrack.AddLayer(layer3);
    // videoTrack.AddLayer(layer4);
    // videoTrack.AddLayer(layer5);


    
    // 音频
    MB::MBAudioTrack audioTrack;

    MB::MBAudioLayer audioLayer;
    audioLayer.SetTime(0.0, 25.0);

    // MB::MBAudioFragment audioFragment;
    // audioFragment.LoadAudioFile("./error_test_video.mp4");

    MB::MBAudioFragment audioFragment2;
    audioFragment2.LoadAudioFile("./1.aac");
    audioFragment2.SetWeight(0.3);

    MB::MBAudioFragment audioFragment3;
    audioFragment3.LoadAudioFile("./2.aac");
    audioFragment3.SetWeight(0.7);

    // audioLayer.AddAudioFragment(audioFragment);
    audioLayer.AddAudioFragment(audioFragment2);
    audioLayer.AddAudioFragment(audioFragment3);

    audioTrack.AddLayer(audioLayer);

    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
    builder.Process();
    */
}

TEST(MBBuilder, MBBuilder){
    /*
    MB::MBWandBuilder builder("./builder_mp4.mp4");
    builder.SetVideoWH(1280, 720);
    builder.SetVideoFPS(60);
    */
    // builder.Process();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
