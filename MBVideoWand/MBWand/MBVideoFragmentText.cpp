#include "MBWand.hpp"

#ifdef EYER_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <locale.h>
#endif

namespace MB
{
    MBVideoFragmentText::MBVideoFragmentText()
    {

    }

    MBVideoFragmentText::~MBVideoFragmentText()
    {
        //todo transKeyList clear
    }

    MBVideoFragmentText::MBVideoFragmentText(const MBVideoFragmentText & vft)
    {
        *this = vft;
    }

    MBVideoFragmentText & MBVideoFragmentText::operator = (const MBVideoFragmentText & vft)
    {
        fontPath = vft.fontPath;
        text = vft.text;

        r = vft.r;
        g = vft.g;
        b = vft.b;

        size = vft.size;

        posX = vft.posX;
        posY = vft.posY;
        
        for(int i=0; i<vft.transKeyList.getLength(); i++){
            MBTransKey * transKey = nullptr;
            vft.transKeyList.find(i, transKey);
            if(transKey != nullptr){
                MBTransKey * tk = new MBTransKey(* transKey);
                transKeyList.insertBack(tk);
            }
        }

        return *this;
    }

    int MBVideoFragmentText::GetTextWidth()
    {
        if(text.IsEmpty()){
            return 0;
        }

        char * char_str = text.str;
        int char_strLen = strlen(char_str);

#ifdef EYER_PLATFORM_WINDOWS
        wchar_t * str = nullptr;
        int strLen = MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, 0);
        str = new wchar_t[strLen];
        MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, strLen);
#else
        setlocale(LC_CTYPE, "zh_CN.utf8");

        wchar_t * str = nullptr;
        int strLen = mbstowcs(NULL, char_str, 0) + 1;
        str = new wchar_t[strLen];
        int ret = mbstowcs(str, char_str, char_strLen + 1);
#endif

        int x = 0;
        for(int i=0;i<strLen;i++){
            wchar_t c = str[i];

            MBType typeCreator(fontPath);
            typeCreator.Init();
            int index = typeCreator.GenChar(c, size);
            if(index <= 0){
                continue;
            }

            MBTypeBitmap bitmap;
            typeCreator.GetCharBitmap(index, &bitmap);

            MBGLCacheTexture * t = new MBGLCacheTexture();
            t->texture = nullptr;
            t->width = bitmap.width;
            t->height = bitmap.height;
            t->bearingY = bitmap.bearingY;
            t->bearingX = bitmap.bearingX;
            t->advance = bitmap.advance;

            x += t->width;
            if(i < strLen - 1) {
                x += t->advance / 64 - t->width - t->bearingX;
            }
        }

        delete[] str;

        return x;
    }

    int MBVideoFragmentText::SetFontPath(MBString path)
    {
        fontPath = path;
        return 0;
    }

    int MBVideoFragmentText::SetText(MBString _text)
    {
        text = _text;
        return 0;
    }

    int MBVideoFragmentText::SetColor(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
        return 0;
    }

    int MBVideoFragmentText::SetSize(float _size)
    {
        size = _size;
        return 0;
    }

    int MBVideoFragmentText::SetPos(float _x, float _y)
    {
        posX = _x;
        posY = _y;
        return 0;
    }

    float MBVideoFragmentText::GetColorR()
    {
        return r;
    }

    float MBVideoFragmentText::GetColorG()
    {
        return g;
    }

    float MBVideoFragmentText::GetColorB()
    {
        return b;
    }

    float MBVideoFragmentText::GetPosX()
    {
        return posX;
    }

    float MBVideoFragmentText::GetPosY()
    {
        return posY;
    }

    float MBVideoFragmentText::GetSize()
    {
        return size;
    }

    MBVideoFragmentType MBVideoFragmentText::GetType() const
    {
        return MBVideoFragmentType::VIDEO_FRAGMENT_TEXT;
    }

    int MBVideoFragmentText::AddTransKey(double t, float x, float y)
    {
        MBTransKey * transKey = new MBTransKey();
        transKey->t = t;
        transKey->x = x;
        transKey->y = y;
        transKeyList.insertBack(transKey);
        return 0;
    }

    int MBVideoFragmentText::AddScaleKey(double t, float size)
    {
        
    }

    int MBVideoFragmentText::GetLinearTrans(double t, float & x, float & y)
    {   
        if(transKeyList.getLength() == 0){
            x = 0;
            y = 0;
            return 0;
        }

        //todo 封装成方法
        MBLinkedEle<MB::MBTransKey *> * currentEle = transKeyList.head;
        for(int i=0; i< transKeyList.getLength()-1; i++){
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
        for(int i=0; i< transKeyList.getLength(); i++){
            MBTransKey * data = nullptr;
            transKeyList.find(i, data);
            printf("===========outT:%f, t:%f, x:%f, y:%f, z:%f\n", t, data->t, data->x, data->y, data->z);
        }

        MB::MBTransKey * firstdata = nullptr;
        MB::MBTransKey * lastdata = nullptr;
        transKeyList.find(0, firstdata);
        transKeyList.find(transKeyList.getLength()-1, lastdata);

        if(t < firstdata->t){
            x = firstdata->x;
            y = firstdata->y;
            return 0;
        }else if(t > lastdata->t){
            x = lastdata->x;
            y = lastdata->y;
            return 0;
        }

        for(int i=0; i<transKeyList.getLength()-1; i++){
            transKeyList.find(i, firstdata);
            transKeyList.find(i+1, lastdata);

            if(t >= firstdata->t && t < lastdata->t){
                double tPart = (t - firstdata->t)/(lastdata->t - firstdata->t);
                x = tPart * (lastdata->x - firstdata->x) + firstdata->x;
                y = tPart * (lastdata->y - firstdata->y) + firstdata->y;
                return 0;
            }
        }

        return 0;
    }

    int MBVideoFragmentText::GetLinearScale(double t, float & size)
    {

    }
}