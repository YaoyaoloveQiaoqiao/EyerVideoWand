#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragmentVideo::EyerVideoFragmentVideo()
    {

    }

    EyerVideoFragmentVideo::EyerVideoFragmentVideo(const EyerVideoFragmentVideo & fragment)
    {
        *this = fragment;
    }

    EyerVideoFragmentVideo::~EyerVideoFragmentVideo()
    {
        if(videoResource != nullptr){
            delete videoResource;
            videoResource = nullptr;
        }

        for(int i=0;i<transKeyList.getLength();i++){
            EyerTransKey * transKey = nullptr;
            transKeyList.find(i, transKey);
            if(transKey != nullptr){
                delete transKey;
            }
        }
        transKeyList.clear();

        for(int i=0; i<scaleKeyList.getLength(); i++){
            EyerTransKey * scaleKey = nullptr;
            scaleKeyList.find(i, scaleKey);
            if(scaleKey != nullptr){
                delete scaleKey;
            }
        }
        scaleKeyList.clear();
    }

    EyerVideoFragmentVideo & EyerVideoFragmentVideo::operator = (const EyerVideoFragmentVideo & fragment)
    {
        if(this == &fragment){
            return *this;
        }

        path = fragment.path;
        startIndex = fragment.startIndex;
        endIndex = fragment.endIndex;
        startTime = fragment.startTime;
        endTime = fragment.endTime;

        videoResource = nullptr;

        for(int i=0;i<fragment.transKeyList.getLength();i++){
            EyerTransKey * transKey = nullptr;
            fragment.transKeyList.find(i, transKey);
            if(transKey != nullptr){
                EyerTransKey * tk = new EyerTransKey(*transKey);
                transKeyList.insertBack(tk);
            }
        }

        for(int i=0; i<fragment.scaleKeyList.getLength(); i++){
            EyerTransKey * scaleKey = nullptr;
            fragment.scaleKeyList.find(i, scaleKey);
            if(scaleKey != nullptr){
                EyerTransKey * sk = new EyerTransKey(*scaleKey);
                scaleKeyList.insertBack(sk);
            }
        }

        return *this;
    }

    int EyerVideoFragmentVideo::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
            videoResource->SetPath(path);
        }

        return videoResource->GetVideoFrame(avFrame, ts);
    }

    int EyerVideoFragmentVideo::LoadVideoFile(EyerString _path)
    {
        path = _path;

        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
        }

        videoResource->SetPath(path);

        int ret = videoResource->GetVideoDuration(duration);
        if(ret){
            // RedLog("GetVideoDuration Error\n");
        }
        // RedLog("Video Duration:%f\n", duration);

        SetFrameTime(0.0, duration);

        // TODO DEBUG
        /*
        EyerAVFrame frame;
        ret = videoResource.GetVideoFrame(frame, 34.00);
        if(ret){
            EyerLog("Docoder Error");
        }
        EyerLog("Frame TS:%lld\n", frame.GetPTS());
        */

        return 0;
    }

    int EyerVideoFragmentVideo::Print()
    {
        EyerLog("Video Duration:%f\n", duration);
        EyerLog("Start Index: %d, End Index: %d\n", startIndex, endIndex);
        EyerLog("Start Time: %f, End Time: %f\n", startTime, endTime);
        return 0;
    }

    double EyerVideoFragmentVideo::GetDuration()
    {
        return duration;
    }

    int EyerVideoFragmentVideo::SetFrameIndex(int _startIndex, int _endIndex)
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
        return 0;
    }

    int EyerVideoFragmentVideo::SetFrameTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    EyerString EyerVideoFragmentVideo::GetPath()
    {
        // EyerLog("%s\n", path.str);
        return path;
    }


    int EyerVideoFragmentVideo::AddTransKey(double t, float x, float y, float z)
    {
        EyerTransKey * transKey = new EyerTransKey();
        transKey->x = x;
        transKey->y = y;
        transKey->z = z;
        transKey->t = t;
        transKeyList.insertBack(transKey);

        return 0;
    }

    int EyerVideoFragmentVideo::AddScaleKey(double t, float x, float y, float z)
    {
        EyerTransKey * scaleKey = new EyerTransKey();
        scaleKey->x = x;
        scaleKey->y = y;
        scaleKey->z = z;
        scaleKey->t = t;
        scaleKeyList.insertBack(scaleKey);
        return 0;
    }

    int EyerVideoFragmentVideo::GetLinearValue(EyerVideoChangeType type, double t, float & x, float & y, float & z)
    {
        Eyer::EyerLinkedList<EyerTransKey *> * changeKeyList = new Eyer::EyerLinkedList<EyerTransKey *>();
        if(type == EyerVideoChangeType::VIDEO_FRAGMENT_CHANGE_TRANS){
            *changeKeyList = transKeyList;
        }else if(type == EyerVideoChangeType::VIDEO_FRAGMENT_CHANGE_SCALE){
            *changeKeyList = scaleKeyList;
        }
        
        if(changeKeyList->getLength() == 0){
            x = 0;
            y = 0;
            z = 0;
            return 0;
        }

        EyerLinkedEle<Eyer::EyerTransKey *> * currentEle = changeKeyList->head;
        for(int i=0; i< changeKeyList->getLength()-1; i++){
            EyerLinkedEle<Eyer::EyerTransKey *> * temp = currentEle->next;
            while (temp != nullptr){
                if(temp->data->t < currentEle->data->t){
                    Eyer::EyerTransKey * data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if(currentEle->next != nullptr){
                currentEle = currentEle->next;
            }
        }

        Eyer::EyerTransKey * firstdata = nullptr;
        Eyer::EyerTransKey * lastdata = nullptr;
        changeKeyList->find(0, firstdata);
        changeKeyList->find(changeKeyList->getLength()-1, lastdata);

        if(t < firstdata->t){
            x = firstdata->x;
            y = firstdata->y;
            z = firstdata->z;
            return 0;
        }else if(t > lastdata->t){
            x = lastdata->x;
            y = lastdata->y;
            z = lastdata->z;
            return 0;
        }

        for(int i=0; i<changeKeyList->getLength()-1; i++){
            changeKeyList->find(i, firstdata);
            changeKeyList->find(i+1, lastdata);

            if(t >= firstdata->t && t < lastdata->t){
                double tPart = (t - firstdata->t)/(lastdata->t - firstdata->t);
                x = tPart * (lastdata->x - firstdata->x) + firstdata->x;
                y = tPart * (lastdata->y - firstdata->y) + firstdata->y;
                z = tPart * (lastdata->z - firstdata->z) + firstdata->z;
                return 0;
            }
        }

        return 0;
    }

    EyerVideoFragmentType EyerVideoFragmentVideo::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO;
    }
}