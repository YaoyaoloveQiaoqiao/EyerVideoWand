#include "MBWand.hpp"

namespace MB
{
    MBAudioTrack::MBAudioTrack()
    {

    }

    MBAudioTrack::~MBAudioTrack()
    {
        for(int i=0;i<layoutList.getLength();i++){
            MBAudioLayer * layer = nullptr;
            layoutList.find(i, layer);
            if(layer != nullptr){
                delete layer;
            }
        }

        layoutList.clear();
    }

    MBAudioTrack::MBAudioTrack(const MBAudioTrack & track)
    {
        *this = track;
    }

    MBAudioTrack & MBAudioTrack::operator = (const MBAudioTrack &track)
    {
        for(int i=0;i<track.layoutList.getLength();i++){
            MBAudioLayer * layer = nullptr;
            track.layoutList.find(i, layer);
            if(layer != nullptr){
                MBAudioLayer * l = new MBAudioLayer(*layer);
                layoutList.insertBack(l);
            }
        }
        return *this;
    }

    int MBAudioTrack::AddLayer(const MBAudioLayer & layer)
    {
        MBAudioLayer * l = new MBAudioLayer(layer);
        layoutList.insertBack(l);
        return 0;
    }

    double MBAudioTrack::GetCountTime()
    {
        double countTime = 0.0;
        for(int i=0;i<layoutList.getLength();i++){
            MBAudioLayer * layer = nullptr;
            layoutList.find(i, layer);
            if(layer != nullptr){
                if(countTime <= layer->GetEndTime()){
                    countTime = layer->GetEndTime();
                }
            }
        }

        return countTime;
    }


    int MBAudioTrack::RenderFrame(double ts, MBAVFrame & outFrame)
    {
        MBLinkedList<MBAVFrame *> tempFrameManager;
        MBLinkedList<MBAudioLayer *> activeLayerList;
        for(int i=0;i<layoutList.getLength();i++){
            MBAudioLayer * layer = nullptr;
            layoutList.find(i, layer);

            if(layer == nullptr){
                continue;
            }

            if(layer->GetStartTime() > ts){
                continue;
            }
            if(layer->GetEndTime() < ts){
                continue;
            }

            activeLayerList.insertBack(layer);
        }

        MBAVAudioFrameUtil mergeAudioUtil;

        for(int i=0;i<activeLayerList.getLength();i++){
            MBAudioLayer * layer = nullptr;
            activeLayerList.find(i, layer);

            if(layer == nullptr){
                continue;
            }

            MBAVFrame * oFrame = new MBAVFrame();
            oFrame->InitAACFrame(6);
            layer->RenderLayerFrame(ts - layer->GetStartTime(), *oFrame);
            tempFrameManager.insertBack(oFrame);


            float w = layer->GetWeight();
            if(w < 0.0f){
                w = 1.0 / activeLayerList.getLength();
            }

            mergeAudioUtil.AddAudioFrame(*oFrame, w);
        }

        mergeAudioUtil.MergeAudioFrame(outFrame);

        activeLayerList.clear();

        for(int i=0;i<tempFrameManager.getLength();i++){
            MBAVFrame * f = nullptr;
            tempFrameManager.find(i, f);
            if(f != nullptr){
                delete f;
            }
        }
        tempFrameManager.clear();

        return 0;
    }
}