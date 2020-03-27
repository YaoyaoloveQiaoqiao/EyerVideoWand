#include "InterfaceC.h"
#include "EyerWand.hpp"

#include <string.h>
#include <stdlib.h>

int             eyer_wand_c_get_version         (char * version)
{
    int version_len = strlen(EYER_WAND_VERSION);
    memcpy(version, EYER_WAND_VERSION, version_len);
    return 0;
}

int             eyer_wand_c_test_add            (int a, int b)
{
    return a + b;
}

void *          eyer_wand_c_builder_init          (const char * out_path, int width, int height, int fps)
{
    Eyer::EyerWandBuilder * builder = new Eyer::EyerWandBuilder(out_path);
    builder->SetVideoWH(width, height);
    builder->SetVideoFPS(fps);

    return (void *)builder;
}

int             eyer_wand_c_builder_uninit        (void * builder)
{
    Eyer::EyerWandBuilder * builder_p = (Eyer::EyerWandBuilder * )builder;
    if(builder_p != NULL){
        delete builder_p;
    }
    return 0;
}

int             eyer_wand_c_builder_add_video_track   (void * _builder, void * _video_track)
{
    Eyer::EyerWandBuilder * builder = (Eyer::EyerWandBuilder * )_builder;
    Eyer::EyerVideoTrack * videoTrack = (Eyer::EyerVideoTrack *)_video_track;

    return builder->AddVideoTrack(*videoTrack);
}

int             eyer_wand_c_builder_add_audio_track     (void * _builder, void * audio_track)
{
    Eyer::EyerWandBuilder * builder = (Eyer::EyerWandBuilder * )_builder;
    Eyer::EyerAudioTrack * audioTrack = (Eyer::EyerAudioTrack *)audio_track;
    return builder->AddAudioTrack(*audioTrack);
}


int             eyer_wand_c_builder_process             (void * _builder)
{
    Eyer::EyerWandBuilder * builder = (Eyer::EyerWandBuilder *)_builder;
    return builder->Process();
}


void *          eyer_wand_c_video_track_init      ()
{
    Eyer::EyerVideoTrack * videoTrack = new Eyer::EyerVideoTrack();

    return (void *)videoTrack;
}

int             eyer_wand_c_video_track_uninit    (void * video_track)
{
    Eyer::EyerVideoTrack * videoTrack = (Eyer::EyerVideoTrack *)video_track;
    if(videoTrack != NULL){
        delete videoTrack;
    }
    return 0;
}

int             eyer_wand_c_video_track_add_layer(void * _video_track, void * _layer)
{
    Eyer::EyerVideoTrack * video_track = (Eyer::EyerVideoTrack *)_video_track;
    Eyer::EyerVideoLayout * layer = (Eyer::EyerVideoLayout *)_layer;
    return video_track->AddLayer(*layer); 
}

void *          eyer_wand_c_layer_init                (int _startFrameIndex, int _endFrameIndex)
{
    Eyer::EyerVideoLayer * layer = new Eyer::EyerVideoLayer();
    layer->SetFrame(_startFrameIndex, _endFrameIndex);
    return (void *)layer;
}

int             eyer_wand_c_layer_uninit              (void * _layer)
{
    Eyer::EyerVideoLayer * layer = (Eyer::EyerVideoLayer *)_layer;
    if(layer != NULL){
        delete layer;
    }
    return 0;
}

int             eyer_wand_c_layer_add_fragment     (void * _layer, void * _fragment)
{
    Eyer::EyerVideoLayer * layer = (Eyer::EyerVideoLayer *)_layer;
    Eyer::EyerVideoFragmentVideo * fragment = (Eyer::EyerVideoFragmentVideo *)_fragment;
    return layer->AddVideoFragment(fragment);
}

void *          eyer_wand_c_fragment_init                (const char * _out_path)
{
    Eyer::EyerVideoFragmentVideo * fragment = new Eyer::EyerVideoFragmentVideo();
    fragment->LoadVideoFile(_out_path);
    return (void *)fragment;
}

int             eyer_wand_c_fragment_uninit              (void * _fragment)
{
    Eyer::EyerVideoFragmentVideo * fragment = (Eyer::EyerVideoFragmentVideo *)_fragment;
    if(fragment != NULL){
        delete fragment;
    }
    return 0;
}

int             eyer_wand_c_fragment_add_transkey        (void * _fragment, double t, float x, float y, float z)
{
    Eyer::EyerVideoFragmentVideo * fragment = (Eyer::EyerVideoFragmentVideo *)_fragment;
    return fragment->AddTransKey(t, x, y, z);
}

int             eyer_wand_c_fragment_add_scalekey        (void * _fragment, double t, float x, float y, float z)
{
    Eyer::EyerVideoFragmentVideo * fragment = (Eyer::EyerVideoFragmentVideo *)_fragment;
    return fragment->AddScaleKey(t, x, y, z);
}

void *          eyer_wand_c_audio_track_init             ()
{
    Eyer::EyerAudioTrack * audioTrack = new  Eyer::EyerAudioTrack();
    return (void *)audioTrack;
}

int             eyer_wand_c_audio_track_uninit           (void * _audio_track)
{
    Eyer::EyerAudioTrack * audioTrack = (Eyer::EyerAudioTrack *)_audio_track;
    if(audioTrack != NULL){
        delete audioTrack;
    }
    return 0;
}

int             eyer_wand_c_audio_track_add_layer        (void * _audio_track, void * _layer)
{
    Eyer::EyerAudioTrack * audioTrack = (Eyer::EyerAudioTrack *)_audio_track;
    Eyer::EyerAudioLayer * audioLayer = (Eyer::EyerAudioLayer *)_layer;
    audioTrack->AddLayer(*audioLayer);
}

void *          eyer_wand_c_audio_layer_init             (double _startTime, double _endTime)
{
    Eyer::EyerAudioLayer * audioLayer = new Eyer::EyerAudioLayer();
    audioLayer->SetTime(_startTime, _endTime);
    return (void *)audioLayer;
}

int             eyer_wand_c_audio_layer_uninit           (void * _audio_layer)
{
    Eyer::EyerAudioLayer * audioLayer = (Eyer::EyerAudioLayer *)_audio_layer;
    if(audioLayer != NULL){
        delete audioLayer;
    }
    return 0;
}

int             eyer_wand_c_audio_layer_add_fragment     (void * _audio_layer, void * _audio_fragment)
{
    Eyer::EyerAudioLayer * audioLayer = (Eyer::EyerAudioLayer *)_audio_layer;
    Eyer::EyerAudioFragment * audioFragment = (Eyer::EyerAudioFragment *)_audio_fragment;
    audioLayer->AddAudioFragment(*audioFragment);
}

void *          eyer_wand_c_audio_fragment_init          (const char * _out_path)
{
    Eyer::EyerAudioFragment * audioFragment = new Eyer::EyerAudioFragment();
    audioFragment->LoadAudioFile(_out_path);
    return (void *)audioFragment;
}

int             eyer_wand_c_audio_fragment_uninit        (void * _audio_fragment)
{
    Eyer::EyerAudioFragment * audioFragment = (Eyer::EyerAudioFragment *)_audio_fragment;
    if(audioFragment != NULL){
        delete audioFragment;
    }
    return 0;
}

void *          eyer_wand_c_text_fragment_init          (const char * _out_path, char * text)
{
    Eyer::EyerVideoFragmentText * fragmentText = new Eyer::EyerVideoFragmentText();
    fragmentText->SetFontPath(_out_path);
    fragmentText->SetText(text);
    return (void *)fragmentText;
}

int             eyer_wand_c_text_fragment_uninit        (void * _text_fragment)
{
    Eyer::EyerVideoFragmentText * fragmentText = (Eyer::EyerVideoFragmentText *)_text_fragment;
    if(fragmentText != NULL){
        delete fragmentText;
    }
    return 0;
}

int             eyer_wand_c_text_fragment_style         (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width)
{
    Eyer::EyerVideoFragmentText * videoFragmentText = (Eyer::EyerVideoFragmentText *)_text_fragment;
    videoFragmentText->SetSize(size);
    videoFragmentText->SetColor(r, g, b);
    int width = videoFragmentText->GetTextWidth();
    videoFragmentText->SetPos(video_width / 2.0 - width / 2.0, y);
    return 0;
}

int             eyer_wand_c_layer_add_text_fragment     (void * _layer, void * _fragment)
{
    Eyer::EyerVideoLayer * layer = (Eyer::EyerVideoLayer *)_layer;
    Eyer::EyerVideoFragmentText * fragment = (Eyer::EyerVideoFragmentText *)_fragment;
    return layer->AddVideoFragment(fragment);
}

