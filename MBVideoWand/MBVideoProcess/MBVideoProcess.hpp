#ifndef	EYER_LIB_AV_WAND_PROCESS_H
#define	EYER_LIB_AV_WAND_PROCESS_H

#include "MBCore/MBCore.hpp"
#include "MBAV/MBAV.hpp"

namespace MB
{
    class MBVPResource;
    class MBVPAudioRes;
    class MBVPTrack;

    class MBVPVideoTrack;
    class MBVPAudioTrack;

    class MBVPVideoImage;

    class MBVPTrack
    {
    public:
    };

    class MBVPVideoTrack : public MBVPTrack
    {
    public:
        MBVPVideoTrack();
        ~MBVPVideoTrack();
    };

    class MBVPAudioTrack : public MBVPTrack
    {
    private:
        std::vector<MBVPAudioRes *> audioList;
        MBAVEncoder encoder;
    public:
        MBVPAudioTrack();
        ~MBVPAudioTrack();

        int AddAudioRes(MBVPAudioRes & audioRes);

        double GetDuration();

        int RenderToFile(MBString outPath);
    };

    class MBVPResource
    {
    private:
        MBString resPath;
        int streamIndex = 0;

        double position = 0;
        double cutterStartTime = 0;
        double cutterEndTime = 0;

        double duration = -1.0;

        // 读取器和解码器不可复制
        MBAVReader * reader = nullptr;
        MBAVDecoder * decoder = nullptr;
    public:
        MBVPResource();
        MBVPResource(MBVPResource & audioRes);

        ~MBVPResource();

        MBVPResource & operator = (MBVPResource & audioRes);

        int SetPath(MBString _resPath);
        int SetStream(int streamIndex);
        int SetPosition(double startTime);
        int SetCutter(double startTime, double endTime);

        MBString GetRes();
        int GetStreamIndex();
        double GetPosition();
        double GetCutterStartTime();
        double GetCutterEndTime();

        double GetDuration();

        int GetFrame(MBAVFrame * avFrame);
    };


    class MBVPAudioRes : public MBVPResource
    {
    public:

    };

    class MBVPVideoImage
    {
    public:
        MBVPVideoImage();
        ~MBVPVideoImage();

        int GetBitmap(MBAVBitmap & bitmap);

        int LoadFromImageFile(MBString path);
    };

    class MBVPVideoRes : public MBVPResource
    {
    private:

    public:
        MBVPVideoRes();
        ~MBVPVideoRes();
    };
}

#endif
