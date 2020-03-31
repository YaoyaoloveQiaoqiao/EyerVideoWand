#include "MBWand.hpp"

namespace MB
{
    MBAudioLayer::MBAudioLayer()
    {

    }

    int MBAudioLayer::SetWeight(float _weight)
    {
        weight = _weight;
        return 0;
    }

    float MBAudioLayer::GetWeight()
    {
        return weight;
    }

    MBAudioLayer::~MBAudioLayer()
    {
        for(int i=0;i<audioFragmentList.getLength();i++){
            MBAudioFragment * audio = nullptr;
            audioFragmentList.find(i, audio);
            if(audio != nullptr){
                delete audio;
            }
        }
        audioFragmentList.clear();
    }

    MBAudioLayer::MBAudioLayer(const MBAudioLayer & layer)
    {
        *this = layer;
    }

    MBAudioLayer & MBAudioLayer::operator = (const MBAudioLayer & layer)
    {
        startTime = layer.startTime;
        endTime = layer.endTime;

        for(int i=0;i<layer.audioFragmentList.getLength();i++){

            MBAudioFragment * audio = nullptr;
            layer.audioFragmentList.find(i, audio);

            if(audio != nullptr){
                MBAudioFragment * a = new MBAudioFragment(*audio);
                this->audioFragmentList.insertBack(a);
            }
        }

        return *this;
    }

    int MBAudioLayer::SetTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    int MBAudioLayer::AddAudioFragment(const MBAudioFragment & audio)
    {
        MBAudioFragment * a = new MBAudioFragment(audio);
        audioFragmentList.insertBack(a);
        return 0;
    }

    double MBAudioLayer::GetStartTime()
    {
        return startTime;
    }

    double MBAudioLayer::GetEndTime()
    {
        return endTime;
    }

    int MBAudioLayer::RenderLayerFrame(double ts, MBAVFrame & outFrame)
    {
        MBAVAudioFrameUtil mergeAudioUtil;

        int audioCount = audioFragmentList.getLength();
        for(int i=0;i<audioFragmentList.getLength();i++){
            MBAudioFragment * audio = nullptr;
            audioFragmentList.find(i, audio);
            if(audio != nullptr){
                MBAVFrame frame;
                audio->ReaderAVFrame(ts, frame);

                float w = audio->GetWeight();
                if(w < 0.0f){
                    w = 1.0 / audioCount;
                }
                mergeAudioUtil.AddAudioFrame(frame, w);
            }
        }
        
        mergeAudioUtil.MergeAudioFrame(outFrame);

        return 0;
    }
}