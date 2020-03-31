#include "MBVideoProcess.hpp"

namespace MB
{
    MBVPResource::MBVPResource()
    {

    }

    MBVPResource::MBVPResource(MBVPResource & audioRes)
    {
        *this = audioRes;
    }

    MBVPResource::~MBVPResource()
    {
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }
    }

    MBVPResource & MBVPResource::operator = (MBVPResource & audioRes)
    {
        resPath = audioRes.resPath;
        streamIndex = audioRes.streamIndex;
        position = audioRes.position;
        cutterStartTime = audioRes.cutterStartTime;
        cutterEndTime = audioRes.cutterEndTime;
        duration = audioRes.duration;

        reader = nullptr;
        decoder = nullptr;

        return *this;
    }

    int MBVPResource::SetPath(MBString _resPath)
    {
        resPath = _resPath;
        return 0;
    }

    int MBVPResource::SetStream(int _streamIndex)
    {
        if(_streamIndex < 0){
            _streamIndex = 0;
        }
        streamIndex = _streamIndex;
        return 0;
    }

    int MBVPResource::SetPosition(double startTime)
    {
        if(startTime < 0){
            startTime = 0;
        }
        position = startTime;
        return 0;
    }

    int MBVPResource::SetCutter(double startTime, double endTime)
    {
        if(startTime < 0){
            startTime = 0;
        }

        if(endTime < startTime){
            endTime = startTime;
        }
        cutterStartTime = startTime;
        cutterEndTime = endTime;
        return 0;
    }

    MBString MBVPResource::GetRes()
    {
        return resPath;
    }

    int MBVPResource::GetStreamIndex()
    {
        return streamIndex;
    }

    double MBVPResource::GetPosition()
    {
        return position;
    }

    double MBVPResource::GetCutterStartTime()
    {
        return cutterStartTime;
    }

    double MBVPResource::GetCutterEndTime()
    {
        return cutterEndTime;
    }

    double MBVPResource::GetDuration()
    {
        if(duration > 0.0){
            return duration;
        }

        MB::MBAVReader reader(GetRes());
        int ret = reader.Open();
        if(ret){
            duration = -1.0;
            return duration;
        }

        MBAVStream audioStream;
        ret = reader.GetStream(audioStream, streamIndex);
        if(ret){
            duration = -1.0;
            return duration;
        }

        MBAVDecoder decoder;
        decoder.Init(&audioStream);

        int fremeSize = decoder.GetFrameSize();
        int sampleRate = decoder.GetSampleRate();

        int frameCount = 0;
        while(1){
            MBAVPacket packet;
            ret = reader.Read(&packet);
            if(ret){
                break;
            }

            frameCount++;
        }

        duration = frameCount * fremeSize * 1.0 / sampleRate;

        reader.Close();

        return duration;
    }



    int MBVPResource::GetFrame(MBAVFrame * avFrame)
    {
        if(reader == nullptr){
            reader = new MBAVReader(GetRes());
            int ret = reader->Open();
            if(ret){
                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }

            MBAVStream stream;
            ret = reader->GetStream(stream, GetStreamIndex());
            if(ret){
                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }

            if(decoder != nullptr){
                delete decoder;
                decoder = nullptr;
            }

            decoder = new MBAVDecoder();
            ret = decoder->Init(&stream);
            if(ret){
                delete decoder;
                decoder = nullptr;

                reader->Close();
                delete reader;
                reader = nullptr;
                return -1;
            }
        }

        MBAVPacket packet;
        int ret = reader->Read(&packet);
        if(ret){
            reader->Close();
            delete reader;
            reader = nullptr;
            return -2;
        }
        decoder->SendPacket(&packet);
        while(1){
            ret = decoder->RecvFrame(avFrame);
            if(ret){
                break;
            }

            return 0;
        }

        reader->Close();
        delete reader;
        reader = nullptr;

        return -3;
    }
}
