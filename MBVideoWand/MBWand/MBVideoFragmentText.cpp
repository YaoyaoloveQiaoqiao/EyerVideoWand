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
}