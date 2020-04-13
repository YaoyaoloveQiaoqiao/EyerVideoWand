#include "MBWand.hpp"
#include <stdio.h>

namespace MB {
    MBVideoFragmentFrameSequential::MBVideoFragmentFrameSequential()
    {

    }

    MBVideoFragmentFrameSequential::~MBVideoFragmentFrameSequential()
    {

    }

    MBVideoFragmentFrameSequential::MBVideoFragmentFrameSequential(const MBVideoFragmentFrameSequential &vft)
    {
        *this = vft;
    }

    MBVideoFragmentFrameSequential & MBVideoFragmentFrameSequential::operator = (const MBVideoFragmentFrameSequential &vft)
    {
        path = vft.path;
        fileNum = vft.fileNum;
        model = vft.model;

        x = vft.x;
        y = vft.y;
        z = vft.z;

        scaleX = vft.scaleX;
        scaleY = vft.scaleY;
        scaleZ = vft.scaleZ;

        fps = vft.fps;

        return *this;
    }

    MBVideoFragmentType MBVideoFragmentFrameSequential::GetType() const
    {
        return MBVideoFragmentType::VIDEO_FRAGMENT_FRAME_SEQUENTIAL;
    }


    int MBVideoFragmentFrameSequential::GetData(MBMat4x4 & mvp, MBGLTexture * targetTexture, double time, MBVideoTrackRenderParams * params)
    {
        int frameIndex = (int)(time * fps);

        if(model == 0 && frameIndex >= fileNum){
            return -1;
        }
        if(model == 1 && frameIndex >= fileNum){
            frameIndex = fileNum -1;
        }
        if(model == 2 && frameIndex >= fileNum){
            frameIndex = frameIndex%fileNum;
        }

        MBString picNameNum = MBString::Number(frameIndex, "%03d");

        MBString imagePath = path + "/" + picNameNum +".png";

        // 读取图片
        int width, height, nrChannels;
        unsigned char * rgba = stbi_load(imagePath.str, &width, &height, &nrChannels, 0);
        if(width <= 0){
            MBLog("imagePath:%s, width:%d, height:%d, nrChannels:%d\n",imagePath.str, width, height, nrChannels);
        }

        /*
        FILE * f = fopen("./aaa.rgba", "wb");
        fwrite(rgba, 1, width * height * nrChannels, f);
        fclose(f);
        */

        targetTexture->SetDataRGBAChannel(rgba, width, height);

        MBMat4x4 ortho;
        int w = params->videoW;
        int h = params->videoH;
        ortho.SetOrtho(- w / 2.0, w / 2.0, h / 2.0, - h / 2.0, 0.0f, 1000.0f);

        MBMat4x4 scale;
        if(scaleX == 0.0 && scaleY == 0.0){
            scaleX = w;
            scaleY = h;
        }
        scale.SetScale(scaleX / 2, scaleY / 2, scaleY / 2);
        MBMat4x4 trans;
        trans.SetTrans(x, y, z);
        mvp = ortho * trans * scale ;

        return 0;
    }

    int MBVideoFragmentFrameSequential::SetDirPathModel(MBString _path, int _fileNum, int _model)
    {
        path = _path;
        fileNum = _fileNum;
        model = _model;
        return 0;
    }

    int MBVideoFragmentFrameSequential::SetScale(float _scaleX, float _scaleY, float _scaleZ)
    {
        scaleX = _scaleX;
        scaleY = _scaleY;
        scaleZ = _scaleZ;
        return 0;
    }

    int MBVideoFragmentFrameSequential::SetTrans(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
        return 0;
    }
}