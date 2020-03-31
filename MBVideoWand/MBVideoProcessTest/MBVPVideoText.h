//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
#define EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H

#include <gtest/gtest.h>
#include "MBVideoProcess/MBVideoProcess.hpp"

#include "MBGL/MBGL.hpp"
#include "MBYUV/MBYUV.hpp"

TEST(MBVideoWand, Video){
    MB::MBAVWriter writer("/home/redknot/Videos/number.mp4");

    writer.Open();

    MB::MBAVEncoder encoder;
    MB::EncoderParam param;
    param.codecId = MB::CodecId::CODEC_ID_H264;
    param.width = 1920;
    param.height = 1080;
    encoder.Init(&param);

    int streamId = writer.AddStream(&encoder);

    writer.Close();
}

TEST(GenVideo, GenVideo){
    int width = 1280;
    int height = 720;

    MB::MBAVWriter writer("/home/redknot/Videos/encoder_number_10s_mp4.mp4");
    writer.Open();

    MB::MBAVEncoder encoder;
    MB::EncoderParam encoderParam;
    encoderParam.width = width;
    encoderParam.height = height;
    encoderParam.codecId = MB::CodecId::CODEC_ID_H264;
    encoder.Init(&encoderParam);

    int videoStreamIndex = writer.AddStream(&encoder);

    writer.WriteHand();

    MB::MBGLWindow windows("GL Canvas", width, height);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

    MB::MBGLFrameBuffer frameBuffer(width, height);

    MB::MBGLTextDraw textDraw("./Manjari-Bold.otf");
    textDraw.SetText("Redknot Miaomiao ABC GL gg");
    textDraw.SetColor(0.0, 1.0, 0.0);
    textDraw.SetSize(100);

    textDraw.SetPos(0, height / 2);

    frameBuffer.AddComponent(&textDraw);

    int m_sec = 0;

    for(int i=0;i<10 * 25;i++){
        windows.Clear();

        MB::MBString timeStr = MB::MBString::Number(m_sec / 1000 / 60) + ":" + MB::MBString::Number(m_sec / 1000 % 60) + ":" + MB::MBString::Number(m_sec % 1000);

        m_sec += 40;

        textDraw.SetText(timeStr);
        textDraw.SetColor(1.0, 0.0, 0.0);
        textDraw.Viewport(width, height);
        frameBuffer.Draw();

        unsigned char * rgbData = (unsigned char * )malloc(width * height * 3);
        frameBuffer.ReadPixel(0, 0, width, height, rgbData);

        unsigned char * y = (unsigned char *)malloc(width * height);
        unsigned char * u = (unsigned char *)malloc(width * height / 4);
        unsigned char * v = (unsigned char *)malloc(width * height / 4);

        MB::MBYUV yuvCon;
        yuvCon.RGB2YUV420(width, height, rgbData, y, u, v);

        MB::MBAVFrame frame;
        frame.SetPTS(i);
        frame.SetVideoData420P(y, u, v, width, height);

        encoder.SendFrame(&frame);
        while(1){
            MB::MBAVPacket pkt;
            int ret = encoder.RecvPacket(&pkt);
            if(ret){
                break;
            }

            MB::MBAVRational encoderTimebase;
            encoder.GetTimeBase(encoderTimebase);

            MB::MBAVRational streamTimebase;
            writer.GetStreamTimeBase(streamTimebase, videoStreamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(videoStreamIndex);
            writer.WritePacket(&pkt);
        }

        free(y);
        free(u);
        free(v);

        free(rgbData);

        windows.Loop();
    }

    encoder.SendFrame(nullptr);
    while(1){
        MB::MBAVPacket pkt;
        int ret = encoder.RecvPacket(&pkt);
        if(ret){
            break;
        }

        MB::MBAVRational encoderTimebase;
        encoder.GetTimeBase(encoderTimebase);

        MB::MBAVRational streamTimebase;
        writer.GetStreamTimeBase(streamTimebase, videoStreamIndex);

        pkt.RescaleTs(encoderTimebase, streamTimebase);

        pkt.SetStreamId(videoStreamIndex);
        writer.WritePacket(&pkt);
    }

    writer.Close();

    windows.Close();
}

#endif //EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
