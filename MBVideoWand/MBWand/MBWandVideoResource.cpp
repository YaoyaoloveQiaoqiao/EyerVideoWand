#include "MBWand.hpp"

namespace MB
{
    MBWandVideoResource::MBWandVideoResource()
    {

    }

    MBWandVideoResource::~MBWandVideoResource()
    {
        for(int i=0;i<decoderLineList.getLength();i++){
            MBVideoDecoderLine * decoderLine = nullptr;
            decoderLineList.find(i, decoderLine);
            if(decoderLine != nullptr){
                delete decoderLine;
            }
        }
        decoderLineList.clear();
    }

    int MBWandVideoResource::GetVideoFrame(MBAVFrame & avFrame, double ts)
    {
        // MBLog("Deocde Line: %d\n", decoderLineList.getLength());
        MBVideoDecoderLine * decoderLine = nullptr;
        for(int i=0;i<decoderLineList.getLength();i++) {
            MBVideoDecoderLine * dl = nullptr;
            decoderLineList.find(i, dl);
            if(ts >= dl->GetStartTime()){
                decoderLine = dl;
            }
        }

        if(decoderLine == nullptr){
            decoderLine = new MBVideoDecoderLine(resPath, ts);
            decoderLineList.insertBack(decoderLine);
        }

        decoderLine->GetFrame(avFrame, ts);

        return 0;
    }

    int MBWandVideoResource::GetVideoDuration(double & duration)
    {
        int finalRet = 0;

        MB::MBAVReader reader(resPath);
        int videoStreamIndex = -1;
        int streamCount = 0;
        MBAVStream avStream;

        int ret = reader.Open();
        if(ret){
            finalRet = -1;
            goto END;
        }

        streamCount = reader.GetStreamCount();
        for(int i=0;i<streamCount;i++){
            MBAVStream stream;
            ret = reader.GetStream(stream, i);
            if(ret){
                continue;
            }

            if(stream.GetStreamType() == MBAVStreamType::STREAM_TYPE_VIDEO){
                videoStreamIndex = i;
            }
        }

        if(videoStreamIndex < 0){
            finalRet = -1;
            goto END;
        }

        ret = reader.GetStream(avStream, videoStreamIndex);
        if(ret){
            finalRet = -1;
            goto END;
        }

        finalRet = 0;
        duration = avStream.GetDuration();

    END:
        ret = reader.Close();

        return finalRet;
    }
}