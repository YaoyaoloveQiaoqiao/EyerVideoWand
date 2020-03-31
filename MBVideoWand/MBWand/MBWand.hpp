#ifndef	EYER_LIB_AV_WAND_H
#define	EYER_LIB_AV_WAND_H

#include "MBGL/MBGL.hpp"
#include "MBGLWindow/MBGLWindow.hpp"
#include "MBCore/MBCore.hpp"
#include "MBAV/MBAV.hpp"
#include "MBGLCustomComponent/MBGLCustomComponent.hpp"

#define MB_WAND_VERSION "MBWand 1.0.0"

namespace MB {
    class MBWand;
    class MBWandDebug;

    class MBWandResourse;

    class MBWandVideoResource;
    class MBWandAudioResource;

    class MBTrack;
    class MBVideoTrack;
    class MBVideoLayout;
    class MBWandBuilder;

    class MBVideoFragment;
    class MBAudioFragment;

    class MBVideoDecoderLine;
    class MBTransKey;

    class MBAudioLayer;

    class MBWand {
    public:
        MBWand();

        ~MBWand();
    };

    class MBWandResource {
    public:
        MBString resPath;
    public:
        MBWandResource();

        ~MBWandResource();

        int SetPath(MBString resPath);
    };

    class MBVideoDecoderLine
    {
    public:
        MBVideoDecoderLine(MBString resPath, double initStart, MBAVStreamType type = MBAVStreamType::STREAM_TYPE_VIDEO);
        ~MBVideoDecoderLine();

        int GetFrame(MBAVFrame & frame, double ts);

        double GetStartTime();
    private:
        int ReadFrame();
        int SelectFrameInList(MBAVFrame * & frame, double ts);

        int fileEndFlag = 0;

        double initStart = 0.0;
        MBString resPath;

        MBAVReader * reader = nullptr;
        MBAVDecoder * decoder = nullptr;
        int videoStreamIndex = -1;

        MBLinkedList<MBAVFrame *> frameList;
    };

    class MBWandVideoResource : public MBWandResource {
    public:
        MBWandVideoResource();
        ~MBWandVideoResource();

        int GetVideoDuration(double & duration);
        int GetVideoFrame(MBAVFrame & avFrame, double ts);

    private:
        MBLinkedList<MBVideoDecoderLine *> decoderLineList;
    };

    class MBWandAudioResource : public MBWandResource {
    public:
        MBWandAudioResource();
        ~MBWandAudioResource();
    };

    enum MBVideoPanelType
    {
        YUV_DATA_PLANE,
        SINGLE_CHANNEL_PLANE
    };

    class MBVideoPanel
    {
    public:
        MBVideoPanel();
        ~MBVideoPanel();

        MBVideoPanel(const MBVideoPanel & panel);
        MBVideoPanel & operator = (const MBVideoPanel & panel);

        int GetYDate(unsigned char * yData);
        int GetUDate(unsigned char * uData);
        int GetVDate(unsigned char * vData);

        int SetData(MBAVFrame & frame);

        int GetW();
        int GetH();


        MBGLTexture targetTexture;


        MBMat4x4 GetMVPMat();

        MBMat4x4 mvp;
    private:
        MBAVFrame frame;
    };


    class MBTrack {
    public:
        virtual ~MBTrack()
        {

        }
    };

    /**
     * 视频轨
     */

    class MBVideoTrackRenderParams
    {
    public:
        int videoW = 0;
        int videoH = 0;
        MB::MBGLFrameBuffer * frameBuffer = nullptr;
        MB::MBGLTextDraw * titleTextDraw = nullptr;
    };

    /**
     * 视频轨
     */
    class MBVideoTrack : public MBTrack {
    public:
        MBVideoTrack();

        ~MBVideoTrack();

        MBVideoTrack(const MBVideoTrack &track);
        MBVideoTrack & operator = (const MBVideoTrack &track);

        int AddLayout(const MBVideoLayout &layout);
        int AddLayer(const MBVideoLayout &layout);

        int GetFrameCount();

        int RenderFrame(int frameIndex, MBVideoTrackRenderParams * params, int fps);
    private:
        MBLinkedList<MBVideoLayout *> layoutList;
    };

    /**
     * 音频轨
     */
    class MBAudioTrack : public MBTrack {
    public:
        MBAudioTrack();
        ~MBAudioTrack();

        MBAudioTrack(const MBAudioTrack & track);
        MBAudioTrack & operator = (const MBAudioTrack &track);

        int AddLayer(const MBAudioLayer & layer);

        double GetCountTime();

        int RenderFrame(double ts, MBAVFrame & outFrame);
    private:
        MBLinkedList<MBAudioLayer *> layoutList;
    };

    class MBAudioLayer {
    public:
        MBAudioLayer();
        ~MBAudioLayer();

        MBAudioLayer(const MBAudioLayer & layer);
        MBAudioLayer & operator = (const MBAudioLayer & layer);

        int RenderLayerFrame(double ts, MBAVFrame & frame);

        int SetTime(double startTime, double endTime);

        int AddAudioFragment(const MBAudioFragment & audio);

        int SetWeight(float _weight);
        float GetWeight();

        double GetStartTime();
        double GetEndTime();
    private:
        double startTime = 0.0;
        double endTime = 0.0;

        float weight = -1.0f;

        MBLinkedList<MBAudioFragment *> audioFragmentList;
    };

     enum MBVideoFilterType
    {
        GAUSSIAN_BLUR,
        ZOOM_BLUR
    };

    class MBVideoLayout {
    public:
        MBVideoLayout();

        ~MBVideoLayout();

        MBVideoLayout(const MBVideoLayout &layout);

        MBVideoLayout & operator = (const MBVideoLayout &layout);


        int AddVideoFragment(const MBVideoFragment * fragment);

        int SetFrame(int startFrameIndex, int endFrameIndex);
        int GetStartFrameIndex();
        int GetEndFrameIndex();


        int GetVideoFragmentCount();
        int GetVideoPanel(MBVideoPanel * panel, MBVideoFragment ** fragmentP, int videoFragmentIndex, int layoutFrameIndex, int fps);
    private:
        int startFrameIndex = 0;
        int endFrameIndex = 0;

        MBLinkedList<MBVideoFragment *> videoFragmentList;
    };

    class MBAudioFragment
    {
    public:
        MBAudioFragment();
        ~MBAudioFragment();

        MBAudioFragment(const MBAudioFragment & fragment);
        MBAudioFragment & operator = (const MBAudioFragment & fragment);

        int SetWeight(float _weight);
        float GetWeight();

        int LoadAudioFile(MBString path);

        int ReaderAVFrame(double ts, MBAVFrame & frame);

    private:
        float weight = -1.0f;

        MBString path;
        MBVideoDecoderLine * decoderLine = nullptr;
    };

    class MBTransKey
    {
    public:
        double t = 0.0;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    public:
        bool operator < (const MBTransKey &key2);

        MBTransKey();
        MBTransKey(const MBTransKey & tk);

        MBTransKey & operator = (const MBTransKey & tk);
    };

    enum MBVideoFragmentType
    {
        VIDEO_FRAGMENT_VIDEO,
        VIDEO_FRAGMENT_TEXT
    };

    class MBVideoFragment
    {
    public:
        virtual ~MBVideoFragment();
        virtual MBVideoFragmentType GetType() const = 0;

        static MBVideoFragment * CopyFragment(const MBVideoFragment * fragment);
    };

    class MBFilterKey
    {
    public:
        double t;
        int filterName;
        int level;

        MBFilterKey();
        MBFilterKey(const MBFilterKey & fk);

        MBFilterKey & operator = (const MBFilterKey & fk);
    };

    enum MBVideoChangeType
    {
        VIDEO_FRAGMENT_CHANGE_TRANS,
        VIDEO_FRAGMENT_CHANGE_SCALE
    };
    class MBVideoFragmentVideo : public MBVideoFragment
    {
    public:
        MBVideoFragmentVideo();
        ~MBVideoFragmentVideo();

        MBVideoFragmentVideo(const MBVideoFragmentVideo & fragment);
        MBVideoFragmentVideo & operator = (const MBVideoFragmentVideo & fragment);

        int LoadVideoFile(MBString path);

        int SetFrameIndex(int startIndex, int endIndex);
        int SetFrameTime(double startTime, double endTime);

        int AddTransKey(double t, float x, float y, float z);
        int AddScaleKey(double t, float x, float y, float z);
        int GetLinearValue(MBVideoChangeType type, double t, float & x, float & y, float & z);

        int AddFilterKey(double t, int filterName, int level);
        int filterLinear(double t, int & filterName, int & level);
        double GetDuration();

        int Print();

        MBString GetPath();

        int GetVideoFrame(MBAVFrame & avFrame, double ts);

        virtual MBVideoFragmentType GetType() const;
    private:
        MBString path;

        int startIndex = 0;
        int endIndex = 0;
        double startTime = 0.0;
        double endTime = 0.0;

        double duration = 0.0;

        MB::MBWandVideoResource * videoResource = nullptr;

        MB::MBLinkedList<MBTransKey *> transKeyList;
        MB::MBLinkedList<MBTransKey *> scaleKeyList;
        MB::MBLinkedList<MBFilterKey *> filterKeyList;

    };

    class MBVideoFragmentText : public MBVideoFragment
    {
    public:
        MBVideoFragmentText();
        ~MBVideoFragmentText();

        MBVideoFragmentText(const MBVideoFragmentText & vft);

        MBVideoFragmentText & operator = (const MBVideoFragmentText & vft);

        int SetFontPath(MBString path);
        int SetText(MBString text);
        int SetColor(float r, float g, float b);
        int SetSize(float size);
        int SetPos(float x, float y);

        int GetTextWidth();

        float GetColorR();
        float GetColorG();
        float GetColorB();

        float GetPosX();
        float GetPosY();

        float GetSize();

        virtual MBVideoFragmentType GetType() const;

    public:
        MBString fontPath;
        MBString text;
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float size = 100.0f;
        float posX = 0.0f;
        float posY = 0.0f;
    };


    class MBWandBuilder
    {
    public:
        MBWandBuilder(MBString path);
        ~MBWandBuilder();

        int SetVideoWH(int w, int h);
        int SetVideoFPS(int fps);

        int AddVideoTrack(const MBVideoTrack & videoTrack);
        int AddAudioTrack(const MBAudioTrack & audioTrack);

        int Process();

    private:
        int VideoProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug = 0);
        int VideoTrackProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug = 0);
        int AudioTrackProcess(MBAVWriter * writer, MBAVEncoder * encoder, int streamIndex, int debug = 0);
    private:
        MBString path;

        int videoWidth = 0;
        int videoHeight = 0;
        int videoFps = 25;

        MBVideoTrack videoTrack;
        MBAudioTrack audioTrack;
    };


    typedef MBVideoLayout MBVideoLayer;

    class MBWandDebug
    {
    public:
        static long long DecoderTime;
        static long long RenderTime;
    };
}

#endif
