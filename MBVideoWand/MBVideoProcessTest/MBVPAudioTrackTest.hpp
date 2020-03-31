#ifndef	EYER_LIB_AV_AUDIO_TRACK_H
#define	EYER_LIB_AV_AUDIO_TRACK_H

#include <gtest/gtest.h>
#include "MBVideoProcess/MBVideoProcess.hpp"

TEST(MBVideoWand, MBVPAudioTrack_Base){
    MB::MBVPAudioTrack audioTrack;
    {
        MB::MBVPAudioRes audioRes;
        audioRes.SetPath("/home/redknot/Videos/A/1403_20_4434.aac");
        audioRes.SetPosition(5.0);
        audioTrack.AddAudioRes(audioRes);
    }

    {
        MB::MBVPAudioRes audioRes;
        audioRes.SetPath("/home/redknot/Videos/A/1403_20_4431.aac");
        audioRes.SetPosition(5.0);
        audioTrack.AddAudioRes(audioRes);
    }

    {
        MB::MBVPAudioRes audioRes;
        audioRes.SetPath("/home/redknot/Videos/A/wei_a.aac");
        audioRes.SetPosition(5.0);
        audioTrack.AddAudioRes(audioRes);
    }

    double duration = audioTrack.GetDuration();
    audioTrack.RenderToFile("/home/redknot/Videos/A/outout.aac");
}

#endif
