#include "MBWand.hpp"
#include <math.h>

namespace MB
{
    MBVideoDecoderLine::MBVideoDecoderLine(MBString _resPath, double _initStart, MBAVStreamType type)
    {
        initStart = _initStart;
        resPath = _resPath;
        reader = new MBAVReader(resPath);
        int ret = reader->Open();
        if(ret){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

        int streamCount = reader->GetStreamCount();
        for(int i=0;i<streamCount;i++){
            MBAVStream stream;
            ret = reader->GetStream(stream, i);
            if(ret){
                continue;
            }

            if(stream.GetStreamType() == type){
                videoStreamIndex = i;
            }
        }

        MBAVStream avStream;
        ret = reader->GetStream(avStream, videoStreamIndex);

        decoder = new MBAVDecoder();
        decoder->Init(&avStream);

        /// TODO reader->SeekFrame(videoStreamIndex, initStart);
    }

    MBVideoDecoderLine::~MBVideoDecoderLine()
    {
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        for(int i=0;i<frameList.getLength();i++){
            MBAVFrame * f = nullptr;
            frameList.find(i, f);
            if(f != nullptr){
                delete f;
            }
        }
        frameList.clear();
    }


    int MBVideoDecoderLine::GetFrame(MBAVFrame & frame, double ts)
    {
        if(ts < initStart){
            return -1;
        }

        MBAVFrame * pFrame = nullptr;

        while(1){
            int ret = SelectFrameInList(pFrame, ts);
            if(ret){
                // 先判断是否已经读取到文件末尾
                if(fileEndFlag){
                    int length = frameList.getLength();
                    // 已经到了末尾，取最后一帧，退出
                    if(frameList.getLength() <= 0){
                        continue;
                        // break;
                    }
                    int lastInex = frameList.getLength() - 1;
                    frameList.find(lastInex, pFrame);

                    break;
                }
                ReadFrame();
                continue;
            }

            // 读取成功
            break;
        }

        if(pFrame == nullptr){
            return -1;
        }

        frame = *pFrame;

        MB::MBAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

        double t = frame.GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        // MBLog("Target TS: %f, Frame TS: %f, D: %f\n", ts, t, t - ts);

        // MBLog("List Size: %d\n", frameList.getLength());

        return 0;
    }

    double MBVideoDecoderLine::GetStartTime()
    {
        if(frameList.getLength() <= 0){
            return initStart;
        }

        MBAVFrame * f = nullptr;
        frameList.find(0, f);
        if(f == nullptr){
            return initStart;
        }

        MB::MBAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

        double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        return t;
    }

    int MBVideoDecoderLine::SelectFrameInList(MBAVFrame * & frame, double ts)
    {
        MBAVFrame * ff = nullptr;
        for(int i=0;i<frameList.getLength();i++){
            MBAVFrame * f = nullptr;
            frameList.find(i, f);
            if(f != nullptr){
                MB::MBAVRational streamTimebase;
                reader->GetStreamTimeBase(streamTimebase, videoStreamIndex);

                double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

                if(t > ts){
                    if(i <= 1){
                        ff = f;
                    }
                    else{
                        // 向前检索一帧进行比较
                        MBAVFrame * lastF = nullptr;
                        frameList.find(i - 1, lastF);

                        double lastFT = lastF->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

                        // MBLog("lastFT - ts : %f\n", abs(lastFT - ts));
                        // MBLog("t - ts : %f\n", abs(t - ts));

                        if(abs(lastFT - ts) < abs(t - ts)){
                            ff = lastF;
                        }
                        else{
                            ff = f;
                        }
                    }

                    break;
                }
                if(t == ts){
                    ff = f;
                    break;
                }
            }
        }

        if(ff == nullptr){
            // 查找失败
            return -1;
        }

        frame = ff;

        while(frameList.getLength() > 30){
            MBAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f != nullptr){
                delete f;
            }
            frameList.deleteEle(0);
        }

        return 0;
    }

    int MBVideoDecoderLine::ReadFrame()
    {
        if(reader == nullptr){
            return -1;
        }
        MBAVPacket pkt;
        int ret = reader->Read(&pkt);
        // MBLog("Read Frame: %d\n", ret);
        if(pkt.GetStreamId() != videoStreamIndex){
            return -1;
        }
        if(ret){
            // 清空解码器
            decoder->SendPacket(nullptr);
            while(1){
                MBAVFrame frame;
                ret = decoder->RecvFrame(&frame);
                if(ret){
                    break;
                }

                MBAVFrame * f = new MBAVFrame(frame);
                frameList.insertBack(f);
            }

            fileEndFlag = 1;
        }
        else{
            decoder->SendPacket(&pkt);
            while(1){
                MBAVFrame frame;
                ret = decoder->RecvFrame(&frame);
                if(ret){
                    break;
                }

                MBAVFrame * f = new MBAVFrame(frame);
                frameList.insertBack(f);
            }
        }
        return 0;
    }
}