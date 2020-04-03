#include <MBGL/MBGL.hpp>
#include "MBWand.hpp"

namespace MB
{
    MBVideoTrack::MBVideoTrack()
    {

    }

    MBVideoTrack::~MBVideoTrack()
    {
        for(int i=0;i<layoutList.getLength();i++){
            MBVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                delete l;
            }
        }

        layoutList.clear();
    }

    MBVideoTrack::MBVideoTrack(const MBVideoTrack & track)
    {
        *this = track;
    }

    MBVideoTrack & MBVideoTrack::operator = (const MBVideoTrack & track)
    {
        if(this == &track){
            return *this;
        }

        for(int i=0;i<track.layoutList.getLength();i++){
            MBVideoLayout * l = nullptr;
            track.layoutList.find(i, l);
            if(l != nullptr){
                MBVideoLayout * _l = new MBVideoLayout(*l);
                layoutList.insertBack(_l);
            }
        }

        return *this;
    }

    int MBVideoTrack::AddLayout(const MBVideoLayout & layout)
    {
        MBVideoLayout * l = new MBVideoLayout(layout);
        layoutList.insertBack(l);
        return 0;
    }

    int MBVideoTrack::AddLayer(const MBVideoLayout &layout)
    {
        return AddLayout(layout);
    }

    int MBVideoTrack::GetFrameCount()
    {
        int frameCount = 0;

        // Find Max Frame Index
        int maxFrameIndex = 0;
        for(int i=0;i<layoutList.getLength();i++){
            MBVideoLayout * l = nullptr;
            layoutList.find(i, l);
            if(l != nullptr){
                int endFrameIndex = l->GetEndFrameIndex();
                if(endFrameIndex > maxFrameIndex){
                    maxFrameIndex = endFrameIndex;
                }
            }
        }

        frameCount = maxFrameIndex;

        return frameCount;
    }


    int MBVideoTrack::RenderFrame(int frameIndex, MBVideoTrackRenderParams * params, int fps)
    {
        MBLinkedList<MBGLComponent *> frameDrawList;
        MBLinkedList<MBGLTexture *> textureList;
        MBLinkedList<MBVideoPanel *> panelList;

        params->frameBuffer->Clear();

        for(int i=0;i<layoutList.getLength();i++){

            MBVideoLayout * layout = nullptr;
            layoutList.find(i, layout);
            if(layout == nullptr){
                continue;
            }

            if(frameIndex < layout->GetStartFrameIndex()){
                continue;
            }
            if(frameIndex > layout->GetEndFrameIndex()){
                continue;
            }

            // MBLog("Layout Frame Index: %d====Layer: %d\n", frameIndex, i);

            int videoFragmentCount = layout->GetVideoFragmentCount();

            for(int fragmentIndex=0;fragmentIndex<videoFragmentCount;fragmentIndex++){
#ifdef EYER_DEBUG
                long long TIME_START_GetVideoPanel = MBTime::GetTime();
#endif
                MBVideoPanel * panel = new MBVideoPanel();
                MBVideoFragment * fragmentP = nullptr;
                int ret = layout->GetVideoPanel(panel, &fragmentP, fragmentIndex, frameIndex - layout->GetStartFrameIndex(), fps, params);
                if(ret){
                    continue;
                }

                panelList.insertBack(panel);

                MBMat4x4 panelMvp = panel->GetMVPMat();

#ifdef EYER_DEBUG
                long long TIME_END_GetVideoPanel = MBTime::GetTime();
#endif

#ifdef EYER_DEBUG
                MBWandDebug::DecoderTime += (TIME_END_GetVideoPanel - TIME_START_GetVideoPanel);
#endif
                // MBLog("Get Panel Success, Width: %d, Height: %d\n", panel.GetW(), panel.GetH());

                if(fragmentP == nullptr){
                    continue;
                }

                if(fragmentP->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
                    MBGLMVPTextureDraw * mvpTextureDraw = new MBGLMVPTextureDraw();
                    mvpTextureDraw->SetTexture(&panel->targetTexture);
                    mvpTextureDraw->SetMVP(panelMvp);
                    frameDrawList.insertBack(mvpTextureDraw);
                    params->frameBuffer->AddComponent(mvpTextureDraw);
                }
                if(fragmentP->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_TEXT){
                    MBVideoFragmentText * vft = (MBVideoFragmentText *)fragmentP;
                    MBGLTextDraw * textDraw = new MBGLTextDraw(vft->fontPath);
                    textDraw->SetText(vft->text);
                    textDraw->SetPos(vft->GetPosX(), vft->GetPosY());
                    textDraw->SetSize(vft->GetSize());
                    textDraw->SetColor(vft->GetColorR(), vft->GetColorG(), vft->GetColorB());

                    frameDrawList.insertBack(textDraw);

                    params->frameBuffer->AddComponent(textDraw);
                }
            }
        }
        params->frameBuffer->AddComponent(params->titleTextDraw);

        params->frameBuffer->Draw();
        params->frameBuffer->ClearAllComponent();

        for(int i=0;i<frameDrawList.getLength();i++){
            MBGLComponent * frameDraw = nullptr;
            frameDrawList.find(i, frameDraw);
            delete frameDraw;
        }
        frameDrawList.clear();

        for(int i=0;i<textureList.getLength();i++){
            MBGLTexture * texture = nullptr;
            textureList.find(i, texture);
            delete texture;
        }
        textureList.clear();

        for(int i=0;i<panelList.getLength();i++){
            MBVideoPanel * panel = nullptr;
            panelList.find(i, panel);
            delete panel;
        }

        panelList.clear();

        return 0;
    }
}