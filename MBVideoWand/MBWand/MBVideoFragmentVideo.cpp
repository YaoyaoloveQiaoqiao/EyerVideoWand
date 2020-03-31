#include "MBWand.hpp"

namespace MB
{
    MBVideoFragmentVideo::MBVideoFragmentVideo()
    {

    }

    MBVideoFragmentVideo::MBVideoFragmentVideo(const MBVideoFragmentVideo & fragment)
    {
        *this = fragment;
    }

    MBVideoFragmentVideo::~MBVideoFragmentVideo()
    {
        if(videoResource != nullptr){
            delete videoResource;
            videoResource = nullptr;
        }

        for(int i=0;i<transKeyList.getLength();i++){
            MBTransKey * transKey = nullptr;
            transKeyList.find(i, transKey);
            if(transKey != nullptr){
                delete transKey;
            }
        }
        transKeyList.clear();

        for(int i=0; i<scaleKeyList.getLength(); i++){
            MBTransKey * scaleKey = nullptr;
            scaleKeyList.find(i, scaleKey);
            if(scaleKey != nullptr){
                delete scaleKey;
            }
        }
        scaleKeyList.clear();

        for(int i=0; i<filterKeyList.getLength(); i++){
            MBFilterKey * filterKey = nullptr;
            filterKeyList.find(i, filterKey);
            if(filterKey != nullptr){
                delete filterKey;
            }
        }
        filterKeyList.clear();
    }

    MBVideoFragmentVideo & MBVideoFragmentVideo::operator = (const MBVideoFragmentVideo & fragment)
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
            MBTransKey * transKey = nullptr;
            fragment.transKeyList.find(i, transKey);
            if(transKey != nullptr){
                MBTransKey * tk = new MBTransKey(*transKey);
                transKeyList.insertBack(tk);
            }
        }

        for(int i=0; i<fragment.scaleKeyList.getLength(); i++){
            MBTransKey * scaleKey = nullptr;
            fragment.scaleKeyList.find(i, scaleKey);
            if(scaleKey != nullptr){
                MBTransKey * sk = new MBTransKey(*scaleKey);
                scaleKeyList.insertBack(sk);
            }
        }

        for(int i=0; i<fragment.filterKeyList.getLength(); i++){
            MBFilterKey * filterKey = nullptr;
            fragment.filterKeyList.find(i, filterKey);
            if(filterKey != nullptr){
                MBFilterKey * fk = new MBFilterKey(*filterKey);
                filterKeyList.insertBack(fk);
            }
        }
        return *this;
    }

    int MBVideoFragmentVideo::GetVideoFrame(MBAVFrame & avFrame, double ts)
    {
        if(videoResource == nullptr){
            videoResource = new MBWandVideoResource();
            videoResource->SetPath(path);
        }

        return videoResource->GetVideoFrame(avFrame, ts);
    }

    int MBVideoFragmentVideo::LoadVideoFile(MBString _path)
    {
        path = _path;

        if(videoResource == nullptr){
            videoResource = new MBWandVideoResource();
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
        MBAVFrame frame;
        ret = videoResource.GetVideoFrame(frame, 34.00);
        if(ret){
            MBLog("Docoder Error");
        }
        MBLog("Frame TS:%lld\n", frame.GetPTS());
        */

        return 0;
    }

    int MBVideoFragmentVideo::Print()
    {
        MBLog("Video Duration:%f\n", duration);
        MBLog("Start Index: %d, End Index: %d\n", startIndex, endIndex);
        MBLog("Start Time: %f, End Time: %f\n", startTime, endTime);
        return 0;
    }

    double MBVideoFragmentVideo::GetDuration()
    {
        return duration;
    }

    int MBVideoFragmentVideo::SetFrameIndex(int _startIndex, int _endIndex)
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
        return 0;
    }

    int MBVideoFragmentVideo::SetFrameTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    MBString MBVideoFragmentVideo::GetPath()
    {
        // MBLog("%s\n", path.str);
        return path;
    }


    int MBVideoFragmentVideo::AddTransKey(double t, float x, float y, float z)
    {
        MBTransKey * transKey = new MBTransKey();
        transKey->x = x;
        transKey->y = y;
        transKey->z = z;
        transKey->t = t;
        transKeyList.insertBack(transKey);

        return 0;
    }

    int MBVideoFragmentVideo::AddScaleKey(double t, float x, float y, float z)
    {
        MBTransKey * scaleKey = new MBTransKey();
        scaleKey->x = x;
        scaleKey->y = y;
        scaleKey->z = z;
        scaleKey->t = t;
        scaleKeyList.insertBack(scaleKey);
        return 0;
    }

    int MBVideoFragmentVideo::GetLinearValue(MBVideoChangeType type, double t, float & x, float & y, float & z)
    {
        MB::MBLinkedList<MBTransKey *> * changeKeyList = new MB::MBLinkedList<MBTransKey *>();
        if(type == MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_TRANS){
            *changeKeyList = transKeyList;
        }else if(type == MBVideoChangeType::VIDEO_FRAGMENT_CHANGE_SCALE){
            *changeKeyList = scaleKeyList;
        }
        
        if(changeKeyList->getLength() == 0){
            x = 0;
            y = 0;
            z = 0;
            return 0;
        }

        MBLinkedEle<MB::MBTransKey *> * currentEle = changeKeyList->head;
        for(int i=0; i< changeKeyList->getLength()-1; i++){
            MBLinkedEle<MB::MBTransKey *> * temp = currentEle->next;
            while (temp != nullptr){
                if(temp->data->t < currentEle->data->t){
                    MB::MBTransKey * data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if(currentEle->next != nullptr){
                currentEle = currentEle->next;
            }
        }

        MB::MBTransKey * firstdata = nullptr;
        MB::MBTransKey * lastdata = nullptr;
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

    MBVideoFragmentType MBVideoFragmentVideo::GetType() const
    {
        return MBVideoFragmentType::VIDEO_FRAGMENT_VIDEO;
    }

    int MBVideoFragmentVideo::AddFilterKey(double t, int filterName, int level)
    {
        MBFilterKey * filterKey = new MBFilterKey();
        filterKey->t = t;
        filterKey->level = level;
        filterKey->filterName = filterName;

        filterKeyList.insertBack(filterKey);
        return 0;
    }

    int MBVideoFragmentVideo::filterLinear(double t, int & filterName, int & level)
    {
        if(filterKeyList.getLength() <= 0){
            return 0;
        }

        MBLinkedEle<MB::MBFilterKey *> * currentEle = filterKeyList.head;
        for(int i=0; i< filterKeyList.getLength()-1; i++){
            MBLinkedEle<MB::MBFilterKey *> * temp = currentEle->next;
            while (temp != nullptr){
                if(temp->data->t < currentEle->data->t){
                    MB::MBFilterKey * data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if(currentEle->next != nullptr){
                currentEle = currentEle->next;
            }
        }

        MBFilterKey * firstData = nullptr;
        MBFilterKey * lastData = nullptr;
        filterKeyList.find(0, firstData);
        filterKeyList.find(filterKeyList.getLength()-1, lastData);

        if(t < firstData->t){
            level = firstData->level;
            filterName = firstData->filterName;
            printf("t<==============filterName:%d, level:%d, t:%f \n", filterName, level, t);

            return 0;
        }else if(t > lastData->t){
            level = lastData->level;
            filterName = lastData->filterName;
            printf("t>==============filterName:%d, level:%d, t:%f \n", filterName, level, t);

            return 0;
        }

        for(int i=0; i<filterKeyList.getLength(); i++){
            filterKeyList.find(i, firstData);
            filterKeyList.find(i+1, lastData);
            printf("=============firstData=filterName:%d, level:%d, t:%f \n", firstData->filterName, firstData->level, firstData->t);
            printf("=============lastData=filterName:%d, level:%d, t:%f \n", lastData->filterName, lastData->level, lastData->t);

            if(t >= firstData->t && t < lastData->t){
                double tPart = (t - firstData->t)/(lastData->t - firstData->t);
                level = (int)(tPart * (lastData->level - firstData->level) + firstData->level);
                filterName = firstData->filterName;
                printf("t==============filterName:%d, level:%d, t:%f \n", filterName, level, t);

                return 0;
            }
        }
        return 0;
    }
}