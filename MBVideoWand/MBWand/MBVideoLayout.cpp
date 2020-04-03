#include "MBWand.hpp"
#include <math.h>
#include "MBGPUDomino/MBGPUDomino.hpp"

namespace MB
{
    MBVideoLayout::MBVideoLayout()
    {

    }

    MBVideoLayout::~MBVideoLayout()
    {
        for(int i=0;i<videoFragmentList.getLength();i++){
            MBVideoFragment * vf = nullptr;
            videoFragmentList.find(i, vf);
            if(vf != nullptr){
                delete vf;
            }
        }

        videoFragmentList.clear();
    }

    int MBVideoLayout::SetFrame(int _startFrameIndex, int _endFrameIndex)
    {
        startFrameIndex = _startFrameIndex;
        endFrameIndex = _endFrameIndex;
        return 0;
    }

    MBVideoLayout::MBVideoLayout(const MBVideoLayout & layout)
    {
        *this = layout;
    }

    MBVideoLayout & MBVideoLayout::operator = (const MBVideoLayout & layout)
    {
        if(this == &layout){
            return *this;
        }

        startFrameIndex = layout.startFrameIndex;
        endFrameIndex = layout.endFrameIndex;

        for(int i=0;i<layout.videoFragmentList.getLength();i++){
            MBVideoFragment * vf = nullptr;
            layout.videoFragmentList.find(i, vf);
            if(vf != nullptr){
                MBVideoFragment * f = MBVideoFragment::CopyFragment(vf);
                videoFragmentList.insertBack(f);
            }
        }

        return *this;
    }

    int MBVideoLayout::GetStartFrameIndex()
    {
        return startFrameIndex;
    }

    int MBVideoLayout::GetEndFrameIndex()
    {
        return endFrameIndex;
    }

    int MBVideoLayout::AddVideoFragment(const MBVideoFragment * fragment)
    {
        MBVideoFragment * f = MBVideoFragment::CopyFragment(fragment);
        videoFragmentList.insertBack(f);

        return 0;
    }

    int MBVideoLayout::GetVideoFragmentCount()
    {
        return videoFragmentList.getLength();
    }

    int MBVideoLayout::GetVideoPanel(MBVideoPanel * panel, MBVideoFragment ** fragmentP,int videoFragmentIndex, int layoutFrameIndex, int fps, MBVideoTrackRenderParams * params)
    {
        MBVideoFragment * fragment = nullptr;
        videoFragmentList.find(videoFragmentIndex, fragment);

        if(fragment == nullptr){
            return -1;
        }

        *fragmentP = fragment;


        MBMat4x4 ortho;
        int w = params->videoW;
        int h = params->videoH;
        ortho.SetOrtho(- w / 2.0, w / 2.0, h / 2.0, - h / 2.0, 0.0f, 1000.0f);

        MBMat4x4 scale;
        scale.SetScale(w / 2.0, h / 2.0, 0.0);
        //scale.SetScale(200, 200, 1.0);

        MBMat4x4 trans;


        if(fragment->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_VIDEO){
            MBVideoFragmentVideo * vfv = (MBVideoFragmentVideo *)fragment;

            MBAVFrame avFrame;
            // double ts = 0.0;
            double ts = 1000 * 1.0 / fps * (layoutFrameIndex);
            ts = ts / 1000.0;
            // MBLog("Ts:%f\n", ts);
            int ret = vfv->GetVideoFrame(avFrame, ts);
            if(ret){
                return -1;
            }

            // avFrame.GetInfo();

            int width = avFrame.GetWidth();
            int height = avFrame.GetHeight();


            MB::MBGLTexture yuv2rgbTexture;
            MBGLFrameBuffer * frameBuffer = new MBGLFrameBuffer(width, height, &yuv2rgbTexture);
            // MBGLFrameBuffer * frameBuffer = new MBGLFrameBuffer(width, height, &panel->targetTexture);
            //MBGLFrameBuffer * frameBuffer = new MBGLFrameBuffer(width, height);

            MBGLYUV2TextureComponent * yuv2texture = new MBGLYUV2TextureComponent();

            unsigned char * yData = nullptr;
            unsigned char * uData = nullptr;
            unsigned char * vData = nullptr;
            MBGLTexture * y = new MBGLTexture();
            MBGLTexture * u = new MBGLTexture();
            MBGLTexture * v = new MBGLTexture();

            if(avFrame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || avFrame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
                yData = (unsigned char *)malloc(width * height);
                avFrame.GetYData(yData);
                uData = (unsigned char *)malloc(width / 2 * height / 2);
                avFrame.GetUData(uData);
                vData = (unsigned char *)malloc(width / 2 * height / 2);
                avFrame.GetVData(vData);

                y->SetDataRedChannel(yData, width, height);
                u->SetDataRedChannel(uData, width / 2, height / 2);
                v->SetDataRedChannel(vData, width / 2, height / 2);

                yuv2texture->SetYTexture(y);
                yuv2texture->SetUTexture(u);
                yuv2texture->SetVTexture(v);
            }

            if(avFrame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || avFrame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
                yData = (unsigned char *)malloc(width * height);
                avFrame.GetYData(yData);
                uData = (unsigned char *)malloc(width * height);
                avFrame.GetUData(uData);
                vData = (unsigned char *)malloc(width * height);
                avFrame.GetVData(vData);

                y->SetDataRedChannel(yData, width, height);
                u->SetDataRedChannel(uData, width, height);
                v->SetDataRedChannel(vData, width, height);

                yuv2texture->SetYTexture(y);
                yuv2texture->SetUTexture(u);
                yuv2texture->SetVTexture(v);
            }


            frameBuffer->Clear();

            frameBuffer->AddComponent(yuv2texture);

            frameBuffer->Draw();

            frameBuffer->ClearAllComponent();


            free(yData);
            free(uData);
            free(vData);

            delete y;
            delete u;
            delete v;

            delete frameBuffer;
            delete yuv2texture;

            MB::MBLinkedList<MBGomino *> blurList;
            int filterName = -1;
            int level = -1;
            vfv->filterLinear(ts, filterName, level);
            MB::MBGominoCopy cp0;
            MB::MBGominoPip pip;
            pip << &cp0;

            if((MBVideoFilterType)filterName == MBVideoFilterType::GAUSSIAN_BLUR){
                for(int j=0; j<level; j++){
                    MB::MBGominoGaussianBlur * gb = new MB::MBGominoGaussianBlur();
                    pip << gb;
                    blurList.insertBack(gb);
                }
            } else if ((MBVideoFilterType)filterName == MBVideoFilterType::ZOOM_BLUR){
                for(int j=0; j<level; j++){
                    MB::MBGominoZoomBlur * zb = new MB::MBGominoZoomBlur();
                    pip << zb;
                    blurList.insertBack(zb);
                }
            }
            
            pip.Go(&yuv2rgbTexture, &panel->targetTexture, width, height);
            for(int i=0; i<blurList.getLength(); i++){
                blurList.clear();
            }
            {
                float x = 0.0;
                float y = 0.0;
                float z = 0.0;

                vfv->GetLinearValue(MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_TRANS, ts, x, y, z);
                trans.SetTrans(x, y, z);

                float scale_x = 0.0;
                float scale_y = 0.0;
                float scale_z = 0.0;
                
                vfv->GetLinearValue(MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_SCALE, ts, scale_x, scale_y, scale_z);
                
                scale.SetScale(scale_x / 2, scale_y / 2, scale_z / 2);
                // scale.SetScale(1920.0 / 2, 1080.0 / 2, scale_z);

                panel->mvp = ortho * trans * scale ;
            }
        }

        if(fragment->GetType() == MBVideoFragmentType::VIDEO_FRAGMENT_TEXT){
            /*
            MBVideoFragmentText * vft = (MBVideoFragmentText *)fragment;

            double ts = 1000 * 1.0 / fps * (layoutFrameIndex);
            ts = ts / 1000.0;

            int width = 0;
            int height = 100;

            MBGLTextDraw textDraw(vft->fontPath);

            textDraw.SetText(vft->text);
            textDraw.SetPos(0.0, 0.0);
            textDraw.SetSize(height);
            textDraw.SetColor(1.0, 0.0, 0.0);

            width = textDraw.GetTextWidth();

            textDraw.Viewport(width, height);

            // MBLog("Font W:%d, H:%d\n", width, height);

            MBGLFrameBuffer frameBuffer(width, height, &panel->targetTexture);

            frameBuffer.Clear();

            frameBuffer.AddComponent(&textDraw);
            frameBuffer.Draw();

            frameBuffer.ClearAllComponent();


            scale.SetScale(100, 100, 1.0);
            panel->mvp = ortho * trans * scale;
            */
        }

        return 0;
    }
}