#include <MBGL/MBGL.hpp>
#include <math.h>

#include "MBWand.hpp"
#include "MBAV/MBAV.hpp"
#include "MBYUV/MBYUV.hpp"

namespace MB
{
    MBWandBuilder::MBWandBuilder(MBString _path)
    {
        path = _path;
        MBLog("MBWandBuilder Init, Path: %s\n", path.str);
    }

    MBWandBuilder::~MBWandBuilder()
    {

    }

    int MBWandBuilder::SetVideoWH(int w, int h)
    {
        videoWidth = w;
        videoHeight = h;
        MBLog("MBWandBuilder Init, W: %d, H:%d\n", videoWidth, videoHeight);
        return 0;
    }

    int MBWandBuilder::SetVideoFPS(int fps)
    {
        videoFps = fps;
        MBLog("MBWandBuilder Init, FPS: %d\n", videoFps);
        return 0;
    }

    int MBWandBuilder::AddVideoTrack(const MBVideoTrack & _videoTrack)
    {
        videoTrack = _videoTrack;
        return 0;
    }

    int MBWandBuilder::AddAudioTrack(const MBAudioTrack & _audioTrack)
    {
        audioTrack = _audioTrack;
        return 0;
    }

    int MBWandBuilder::Process()
    {
        MB::MBAVWriter writer(path);
        writer.Open();

        // AddVideoStream
        MB::MBAVEncoder encoder;
        MB::EncoderParam encoderParam;
        encoderParam.width = videoWidth;
        encoderParam.height = videoHeight;
        encoderParam.fps = videoFps;
        encoderParam.codecId = MB::CodecId::CODEC_ID_H264;
        encoder.Init(&encoderParam);

        int videoStreamIndex = writer.AddStream(&encoder);

        // AddAudioStream
        MB::MBAVEncoder audioEncoder;
        EncoderParam audioEncoderParam;
        audioEncoderParam.codecId = CodecId::CODEC_ID_AAC;
        audioEncoder.Init(&audioEncoderParam);

        int audioStreamIndex = writer.AddStream(&audioEncoder);

        writer.WriteHand();

        // Video
        VideoTrackProcess(&writer, &encoder, videoStreamIndex);

        // Audio
        AudioTrackProcess(&writer, &audioEncoder, audioStreamIndex);

        writer.Close();

        return 0;
    }

    int MBWandBuilder::VideoTrackProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug)
    {
        // 获取 VideoTrack
        // 从layout中获取总帧数
        int frameCount = videoTrack.GetFrameCount();
        MBLog("Frame Count: %d\n", frameCount);

        int width = videoWidth;
        int height = videoHeight;

        MB::MBGLWindow windows("MB Wand", width, height);
        windows.Open();
        // windows.SetBGColor(1.0, 1.0, 1.0, 1.0);
        windows.SetBGColor(0.0, 0.0, 0.0, 1.0);


        MB::MBGLFrameBuffer windowsFrameBuffer(width, height);
        // MB::MBGLTextDraw textProgressDraw("./han_yi_xing_kai_jian.ttf");
        MB::MBGLTextDraw textProgressDraw("./xiao_xiao_yuan_pin_ying.ttf");
        textProgressDraw.SetText("Redknot Miaomiao ABC GL gg");
        textProgressDraw.SetColor(0.0, 0.0, 0.0);
        textProgressDraw.SetSize(50);
        textProgressDraw.SetPos(0, height / 2);


        MBGLTexture canvasRenderTarget;
        MB::MBGLFrameBuffer frameBuffer(width, height, &canvasRenderTarget);

        /*MB::MBGLTextDraw textDraw("./xiao_xiao_yuan_pin_ying.ttf");
        textDraw.SetText("Redknot Miaomiao ABC GL gg");
        textDraw.SetColor(0.0, 1.0, 0.0);
        textDraw.SetSize(50);
        textDraw.SetPos(0, 0 + 50);*/

        //frameBuffer.AddComponent(&textDraw);



        MBGLTexture outRenderTarget;
        MB::MBGLFrameBuffer outFrameBuffer(width, height, &outRenderTarget);

        MB::MBGLSingleTextureDraw canvasDraw;
        canvasDraw.SetTexture(&canvasRenderTarget);

        outFrameBuffer.AddComponent(&canvasDraw);

        for(int frameIndex = 0; frameIndex < frameCount; frameIndex++){
            windows.Clear();

            textProgressDraw.SetColor(1.0, 1.0, 1.0);
            textProgressDraw.SetText(MBString("MB Wand 正 在 生 成 视 频 ： ") + MBString::Number((int)(frameIndex * 1.0 / frameCount * 100)) + " %");
            int progressWidth = textProgressDraw.GetTextWidth();
            textProgressDraw.SetPos((width - progressWidth) / 2, height / 2);

            windowsFrameBuffer.Clear();
            windowsFrameBuffer.AddComponent(&textProgressDraw);
            windowsFrameBuffer.Draw();
            windowsFrameBuffer.ClearAllComponent();


            int msec = (int)(frameIndex * 1.0 / encoder->GetFPS() * 1000);
            /*
            textDraw.SetText(MB::MBString("MB Wand 基情支持") + MB::MBString::Number(msec / 1000 / 60 / 60, "%02d") + ":" +
                                  MB::MBString::Number(msec / 1000 / 60 % 60, "%02d") + ":" +
                                  MB::MBString::Number(msec / 1000 % 60, "%02d") + ":" +
                                  MB::MBString::Number(msec % 1000, "%03d"));
            textDraw.SetPos(0, 0 + 50);
            textDraw.SetColor(1.0, 0.0, 0.0);
            textDraw.Viewport(width, height);
             */

            MBVideoTrackRenderParams params;
            params.videoW = width;
            params.videoH = height;
            params.frameBuffer = &frameBuffer;
            //params.titleTextDraw = &textDraw;

            videoTrack.RenderFrame(frameIndex, &params, videoFps);

            outFrameBuffer.Draw();

            unsigned char * rgbData = (unsigned char * )malloc(videoWidth * videoHeight * 3);
            outFrameBuffer.ReadPixel(0, 0, videoWidth, videoHeight, rgbData);

            unsigned char * y = (unsigned char *)malloc(videoWidth * videoHeight);
            unsigned char * u = (unsigned char *)malloc(videoWidth * videoHeight / 4);
            unsigned char * v = (unsigned char *)malloc(videoWidth * videoHeight / 4);

            MB::MBYUV yuvCon;
            yuvCon.RGB2YUV420(videoWidth, videoHeight, rgbData, y, u, v);

            MB::MBAVFrame frame;
            frame.SetPTS(frameIndex);
            frame.SetVideoData420P(y, u, v, videoWidth, videoHeight);

            encoder->SendFrame(&frame);
            while(1){
                MB::MBAVPacket pkt;
                int ret = encoder->RecvPacket(&pkt);
                if(ret){
                    break;
                }

                MB::MBAVRational encoderTimebase;
                encoder->GetTimeBase(encoderTimebase);

                MB::MBAVRational streamTimebase;
                writer->GetStreamTimeBase(streamTimebase, streamIndex);

                pkt.RescaleTs(encoderTimebase, streamTimebase);

                pkt.SetStreamId(streamIndex);
                writer->WritePacket(&pkt);
            }

            free(y);
            free(u);
            free(v);

            free(rgbData);

            windows.Loop();
        }

        encoder->SendFrame(nullptr);
        while(1){
            MB::MBAVPacket pkt;
            int ret = encoder->RecvPacket(&pkt);
            if(ret){
                break;
            }

            MB::MBAVRational encoderTimebase;
            encoder->GetTimeBase(encoderTimebase);

            MB::MBAVRational streamTimebase;
            writer->GetStreamTimeBase(streamTimebase, streamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(streamIndex);
            writer->WritePacket(&pkt);
        }

        windows.Close();

#ifdef EYER_DEBUG
        MBLog("Decode Time Count : %lld\n", MBWandDebug::DecoderTime);
#endif

        return 0;
    }

    int MBWandBuilder::VideoProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug)
    {
        return 0;
    }

    int MBWandBuilder::AudioTrackProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug)
    {
        // 记录当前写入的长度
        double wirteTime = 0.0;
        while(1){
            int bufferSize = encoder->GetBufferSize();
            int sampSize = bufferSize / 4 / 2;
            double dTime = sampSize * 1.0 / 44100;

            MB::MBAVFrame avFrame;
            avFrame.InitAACFrame(6);

            audioTrack.RenderFrame(wirteTime, avFrame);

            encoder->SendFrame(&avFrame);
            while(1){
                MB::MBAVPacket pkt;
                int ret = encoder->RecvPacket(&pkt);
                if(ret){
                    break;
                }

                MB::MBAVRational encoderTimebase;
                encoder->GetTimeBase(encoderTimebase);

                MB::MBAVRational streamTimebase;
                writer->GetStreamTimeBase(streamTimebase, streamIndex);

                pkt.RescaleTs(encoderTimebase, streamTimebase);

                pkt.SetStreamId(streamIndex);
                writer->WritePacket(&pkt);

                wirteTime += dTime;
            }
            // MBLog("Time: %f\n", wirteTime);

            if(wirteTime >= audioTrack.GetCountTime()){
                break;
            }
        }

        encoder->SendFrame(nullptr);
        while(1){
            MB::MBAVPacket pkt;
            int ret = encoder->RecvPacket(&pkt);
            if(ret){
                break;
            }

            MB::MBAVRational encoderTimebase;
            encoder->GetTimeBase(encoderTimebase);

            MB::MBAVRational streamTimebase;
            writer->GetStreamTimeBase(streamTimebase, streamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(streamIndex);
            writer->WritePacket(&pkt);
        }

        return 0;
    }
}