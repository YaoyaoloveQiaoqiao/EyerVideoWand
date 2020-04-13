#include "MBWand.hpp"

namespace MB
{
    MBVideoFragment * MBVideoFragment::CopyFragment(const MBVideoFragment * fragment)
    {
        MBVideoFragment * f = nullptr;
        if(fragment->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            f = new MBVideoFragmentVideo(*(MBVideoFragmentVideo *)fragment);
        }
        if(fragment->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_TEXT){
            f = new MBVideoFragmentText(*(MBVideoFragmentText *)fragment);
        }
        if(fragment->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_FRAME_SEQUENTIAL){
            f = new MBVideoFragmentFrameSequential(*(MBVideoFragmentFrameSequential *)fragment);
        }
        return f;
    }


    MBVideoFragment::~MBVideoFragment()
    {

    }
}