#include "MBWand.hpp"

namespace MB
{
    MBAudioFragment::MBAudioFragment()
    {

    }

    MBAudioFragment::~MBAudioFragment()
    {
        if(decoderLine != nullptr){
            delete decoderLine;
            decoderLine = nullptr;
        }
    }

    MBAudioFragment::MBAudioFragment(const MBAudioFragment & fragment)
    {
        *this = fragment;
    }

    MBAudioFragment & MBAudioFragment::operator = (const MBAudioFragment & fragment)
    {
        path = fragment.path;
        weight = fragment.weight;
        return *this;
    }

    int MBAudioFragment::LoadAudioFile(MBString _path)
    {
        path = _path;
        return 0;
    }

    int MBAudioFragment::ReaderAVFrame(double ts, MBAVFrame & frame)
    {
        if(decoderLine == nullptr){
            decoderLine = new MBVideoDecoderLine(path, 0.0, MBAVStreamType::STREAM_TYPE_AUDIO);
        }

        decoderLine->GetFrame(frame, ts);

        return 0;
    }

    int MBAudioFragment::SetWeight(float _weight)
    {
        weight = _weight;
        return 0;
    }

    float MBAudioFragment::GetWeight()
    {
        return weight;
    }
}