//
// Created by redknot on 2020/1/5.
//

#include "MBVideoProcess.hpp"

namespace MB
{
    MBVPVideoImage::MBVPVideoImage()
    {

    }

    MBVPVideoImage::~MBVPVideoImage()
    {

    }

    int MBVPVideoImage::GetBitmap(MBAVBitmap & bitmap)
    {
        return 0;
    }

    int MBVPVideoImage::LoadFromImageFile(MBString path)
    {
        MBAVReader reader(path);

        int ret = reader.Open();
        if(ret){
            return -1;
        }

        MBAVStream stream;
        ret = reader.GetStream(stream, 0);
        if(ret){
            return -1;
        }

        MBAVDecoder decoder;
        decoder.Init(&stream);

        while(1){
            MBAVPacket pkt;
            ret = reader.Read(&pkt);

            if(ret){
                break;
            }

            decoder.SendPacket(&pkt);

            while(1){
                MBAVFrame frame;
                ret = decoder.RecvFrame(&frame);
                if(ret){
                    break;
                }

                MBLog("Width:%d\n", frame.GetWidth());
                MBLog("Height:%d\n", frame.GetHeight());
                // frame.GetInfo();

                return 0;
            }
        }

        return -2;
    }
}

