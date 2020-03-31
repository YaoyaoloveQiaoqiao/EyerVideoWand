#include "MBVideoProcess.hpp"

#include <math.h>

namespace MB
{
    MBVPAudioTrack::MBVPAudioTrack()
    {
        EncoderParam param;
        param.codecId = CodecId::CODEC_ID_AAC;
        encoder.Init(&param);
    }

    MBVPAudioTrack::~MBVPAudioTrack()
    {
        for(int i=0;i<audioList.size();i++){
            MBVPAudioRes * res = audioList[i];
            delete res;
        }
        audioList.clear();
    }

    int MBVPAudioTrack::AddAudioRes(MBVPAudioRes & audioRes)
    {
        MBVPAudioRes * resouse = new MBVPAudioRes(audioRes);
        audioList.push_back(resouse);
        return 0;
    }

    double MBVPAudioTrack::GetDuration()
    {
        double duration = 0;
        for(int i=0;i<audioList.size();i++){
            MBVPAudioRes * res = audioList[i];

            if(res->GetDuration() <= 0){
                continue;
            }

            long long d = res->GetDuration() + res->GetPosition();
            if(duration < d){
                duration = d;
            }
        }
        return duration;
    }

    int MBVPAudioTrack::RenderToFile(MBString outPath)
    {
        MB::MBAVWriter writer(outPath);
        int streamIndex = writer.AddStream(&encoder);
        writer.Open();
        writer.WriteHand();

        // 记录当前写入的长度
        double wirteTime = 0.0;

        while(1){
            if(wirteTime >= GetDuration()){
                break;
            }

            int bufferSize = encoder.GetBufferSize();
            int sampSize = bufferSize / 4 / 2;
            double dTime = sampSize * 1.0 / 44100;

            std::vector<MBVPAudioRes *> alternateList;
            for(int i=0;i<audioList.size();i++){
                MBVPAudioRes * res = audioList[i];

                double startTime = res->GetPosition();
                double endTime = startTime + res->GetDuration();

                if(wirteTime >= startTime && wirteTime <= endTime){
                    alternateList.push_back(res);
                }
            }

            // Create Frame
            MB::MBAVFrame avFrame;

            int frameSize = encoder.GetFrameSize();
            int size = encoder.GetBufferSize();

            float * d = (float *)malloc(size);
            for(int i=0;i<size / 4;i++){
                d[i] = 0.1;
            }

            std::vector<float *> mixFrameList;
            for(int i=0;i<alternateList.size();i++){
                MBVPAudioRes * res = alternateList[i];
                MB::MBAVFrame resAvFrame;
                int ret = res->GetFrame(&resAvFrame);
                if(ret){
                    continue;
                }

                float * a = (float *)malloc(size);
                resAvFrame.GetAudioData((unsigned char *)a);
                mixFrameList.push_back(a);
            }

            // printf("Frame Size::%d\n", mixFrameList.size());
            if(mixFrameList.size() > 0){
                for(int i=0;i<size / 4;i++){
                    float kkk = 0.0f;
                    for(int j=0;j<mixFrameList.size();j++){
                        kkk += mixFrameList[j][i];
                    }
                    kkk = kkk / mixFrameList.size();
                    d[i] = kkk;
                }
            }

            for(int i=0;i<mixFrameList.size();i++){
                float * f = mixFrameList[i];
                free(f);
            }
            mixFrameList.clear();

            avFrame.SetAudioData((unsigned char *)d, size, frameSize, 2, MB::MBAVFormat::EYER_AV_SAMPLE_FMT_FLTP);

            free(d);

            encoder.SendFrame(&avFrame);
            while(1){
                MB::MBAVPacket avPacket;
                int ret = encoder.RecvPacket(&avPacket);
                if(ret){
                    break;
                }

                avPacket.SetStreamId(streamIndex);

                writer.WritePacket(&avPacket);

                wirteTime += dTime;
            }
        }

        writer.Close();

        return 0;
    }
}
