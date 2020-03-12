#include <stdio.h>
#include <gtest/gtest.h>
#include <EyerWand/EyerWand.hpp>

TEST(EyerWand, Eyer_Decoder_Line){
    /*
    Eyer::EyerVideoDecoderLine decoderLine("./M_1280_720.mp4", 20.0);

    for(double ts = 20.0; ts < 40.0; ts += 0.01){
        Eyer::EyerAVFrame frame;
        decoderLine.GetFrame(frame, ts);
    }
     */
}

TEST(EyerWand, EyerWandRes_Base){

}

TEST(EyerVideoTrack, EyerWandRes_Base){
    /*
    Eyer::EyerWandBuilder builder("./struct_builder_mp4.mp4");

    Eyer::EyerVideoTrack videoTrack;

    for(int i=0;i<1000;i++){
        Eyer::EyerVideoLayout layout;
        layout.SetFrame(i, i + 1000);

        Eyer::EyerVideoFragment videoFragment;
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

TEST(EyerVideoBuild, EyerVideoBuild_Test){
    int fps = 30;

    Eyer::EyerWandBuilder builder("./struct_builder_vidoe_mp4.mp4");
    builder.SetVideoWH(1920, 1080);
    builder.SetVideoFPS(fps);

    // 视频
    Eyer::EyerVideoTrack videoTrack;

    Eyer::EyerVideoLayout layer;
    layer.SetFrame(0, fps * 5);

    Eyer::EyerVideoLayout layer2;
    //layer2.SetFrame(fps * 5, fps * 5 + fps * 9);
    layer2.SetFrame(0, fps * 9);

    Eyer::EyerVideoLayout layer3;
    // layer3.SetFrame(fps * 9, fps * 9 + fps * 5);
    layer3.SetFrame(0, fps * 5);

    Eyer::EyerVideoLayout layer4;
    layer4.SetFrame(fps * 5, fps * 5 + fps *5);

    Eyer::EyerVideoFragmentVideo videoFragment;
    videoFragment.LoadVideoFile("./M_1280_720.mp4");
    videoFragment.AddTransKey(0.0, 5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.1, -5.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.2, 3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.3, -3.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.4, 2.0, 0.0, 0.0);
    videoFragment.AddTransKey(0.5, 0.0, 0.0, 0.0);

    videoFragment.Print();

    Eyer::EyerVideoFragmentVideo videoFragment2;
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

    videoFragment2.AddTransKey(4.1, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.2, 30.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.3, -30.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.4, 20.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.5, -20.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.6, 10.0, 0.0, 0.0);
    videoFragment2.AddTransKey(4.7, 0.0, 0.0, 0.0);

    videoFragment2.AddTransKey(6.3, 0.0, 0.0, 0.0);
    videoFragment2.AddTransKey(6.4, -30.0, -30.0, 0.0);
    videoFragment2.AddTransKey(6.5, 30.0, 30.0, 0.0);
    videoFragment2.AddTransKey(6.6, -20.0, -20.0, 0.0);
    videoFragment2.AddTransKey(6.7, 20.0, 20.0, 0.0);
    videoFragment2.AddTransKey(6.8, 10.0, 10.0, 0.0);
    videoFragment2.AddTransKey(6.9, 0.0, 0.0, 0.0);

    videoFragment2.Print();


    Eyer::EyerVideoFragmentText videoFragmentText;
    videoFragmentText.SetFontPath("./xiao_xiao_yuan_pin_ying.ttf");
    videoFragmentText.SetText("这里是测试字幕");

    layer.AddVideoFragment(&videoFragment);

    layer2.AddVideoFragment(&videoFragment2);
    layer2.AddVideoFragment(&videoFragmentText);


    Eyer::EyerVideoFragmentVideo videoFragmentImage;
    videoFragmentImage.LoadVideoFile("./3.jpg");

    layer3.AddVideoFragment(&videoFragmentImage);

    Eyer::EyerVideoFragmentVideo videoFragmentImage2;
    videoFragmentImage2.LoadVideoFile("./4.jpg");
    layer4.AddVideoFragment(&videoFragmentImage2);

    //videoTrack.AddLayer(layer);
    videoTrack.AddLayer(layer3);
    videoTrack.AddLayer(layer4);

    // 音频
    Eyer::EyerAudioTrack audioTrack;

    Eyer::EyerAudioLayer audioLayer;
    audioLayer.SetTime(0.0, 10.0);

    Eyer::EyerAudioFragment audioFragment;
    audioFragment.LoadAudioFile("./wei.mp3");

    audioLayer.AddAudioFragment(audioFragment);

    audioTrack.AddLayer(audioLayer);


    builder.AddVideoTrack(videoTrack);
    builder.AddAudioTrack(audioTrack);
    builder.Process();
}

TEST(EyerBuilder, EyerBuilder){
    /*
    Eyer::EyerWandBuilder builder("./builder_mp4.mp4");
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
