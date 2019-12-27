#ifndef	EYER_LIB_AV_H
#define	EYER_LIB_AV_H

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerVPAudioRes;
    class EyerVPTrack;
    class EyerVPVideoTrack;
    class EyerVPAudioTrack;

    class EyerVPTrack
    {
    public:
    };

    class EyerVPVideoTrack : public EyerVPTrack
    {
    public:
    };

    class EyerVPAudioTrack : public EyerVPTrack
    {
    private:
        std::vector<EyerVPAudioRes *> audioList;
    public:
        EyerVPAudioTrack();
        ~EyerVPAudioTrack();

        int AddAudioRes(EyerVPAudioRes & audioRes);
    };

    class EyerVPAudioRes
    {
    private:
        EyerString resPath;
        int streamIndex = 0;

        long long position = 0;
        long long cutterStartTime = 0;
        long long cutterEndTime = 0;
    public:
        EyerVPAudioRes();
        EyerVPAudioRes(EyerVPAudioRes & audioRes);

        ~EyerVPAudioRes();

        EyerVPAudioRes & operator = (EyerVPAudioRes & audioRes);

        int SetPath(EyerString _resPath);
        int SetStream(int streamIndex);

        int SetPosition(long long startTime);
        int SetCutter(long long startTime, long long endTime);

        long long GetDur();


        EyerString GetRes();
        int GetStreamIndex();
        long long GetPosition();
        long long GetCutterStartTime();
        long long GetCutterEndTime();
    };
}

#endif
