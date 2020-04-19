#include "InterfaceC.h"
#include "MBWand.hpp"

#include <string.h>
#include <stdlib.h>

int             mb_c_get_version         (char * version)
{
    int version_len = strlen(MB_WAND_VERSION);
    memcpy(version, MB_WAND_VERSION, version_len);
    return 0;
}

int             mb_c_test_add            (int a, int b)
{
    return a + b;
}

void *          mb_c_builder_init          (const char * out_path, int width, int height, int fps)
{
    MB::MBWandBuilder * builder = new MB::MBWandBuilder(out_path);
    builder->SetVideoWH(width, height);
    builder->SetVideoFPS(fps);

    return (void *)builder;
}

int             mb_c_builder_uninit        (void * builder)
{
    MB::MBWandBuilder * builder_p = (MB::MBWandBuilder * )builder;
    if(builder_p != NULL){
        delete builder_p;
    }
    return 0;
}

int             mb_c_builder_add_video_track   (void * _builder, void * _video_track)
{
    MB::MBWandBuilder * builder = (MB::MBWandBuilder * )_builder;
    MB::MBVideoTrack * videoTrack = (MB::MBVideoTrack *)_video_track;

    return builder->AddVideoTrack(*videoTrack);
}

int             mb_c_builder_add_audio_track     (void * _builder, void * audio_track)
{
    MB::MBWandBuilder * builder = (MB::MBWandBuilder * )_builder;
    MB::MBAudioTrack * audioTrack = (MB::MBAudioTrack *)audio_track;
    return builder->AddAudioTrack(*audioTrack);
}


int             mb_c_builder_process             (void * _builder)
{
    MB::MBWandBuilder * builder = (MB::MBWandBuilder *)_builder;
    return builder->Process();
}


void *          mb_c_video_track_init      ()
{
    MB::MBVideoTrack * videoTrack = new MB::MBVideoTrack();

    return (void *)videoTrack;
}

int             mb_c_video_track_uninit    (void * video_track)
{
    MB::MBVideoTrack * videoTrack = (MB::MBVideoTrack *)video_track;
    if(videoTrack != NULL){
        delete videoTrack;
    }
    return 0;
}

int             mb_c_video_track_add_layer(void * _video_track, void * _layer)
{
    MB::MBVideoTrack * video_track = (MB::MBVideoTrack *)_video_track;
    MB::MBVideoLayout * layer = (MB::MBVideoLayout *)_layer;
    return video_track->AddLayer(*layer); 
}

void *          mb_c_layer_init                (int _startFrameIndex, int _endFrameIndex)
{
    MB::MBVideoLayer * layer = new MB::MBVideoLayer();
    layer->SetFrame(_startFrameIndex, _endFrameIndex);
    return (void *)layer;
}

int             mb_c_layer_uninit              (void * _layer)
{
    MB::MBVideoLayer * layer = (MB::MBVideoLayer *)_layer;
    if(layer != NULL){
        delete layer;
    }
    return 0;
}

int             mb_c_layer_add_fragment     (void * _layer, void * _fragment)
{
    MB::MBVideoLayer * layer = (MB::MBVideoLayer *)_layer;
    MB::MBVideoFragmentVideo * fragment = (MB::MBVideoFragmentVideo *)_fragment;
    return layer->AddVideoFragment(fragment);
}

void *          mb_c_fragment_init                (const char * _out_path)
{
    MB::MBVideoFragmentVideo * fragment = new MB::MBVideoFragmentVideo();
    fragment->LoadVideoFile(_out_path);
    return (void *)fragment;
}

int             mb_c_fragment_uninit              (void * _fragment)
{
    MB::MBVideoFragmentVideo * fragment = (MB::MBVideoFragmentVideo *)_fragment;
    if(fragment != NULL){
        delete fragment;
    }
    return 0;
}

int             mb_c_fragment_add_transkey        (void * _fragment, double t, float x, float y, float z)
{
    MB::MBVideoFragmentVideo * fragment = (MB::MBVideoFragmentVideo *)_fragment;
    return fragment->AddTransKey(t, x, y, z);
}

int             mb_c_fragment_add_scalekey        (void * _fragment, double t, float x, float y, float z)
{
    MB::MBVideoFragmentVideo * fragment = (MB::MBVideoFragmentVideo *)_fragment;
    return fragment->AddScaleKey(t, x, y, z);
}

void *          mb_c_audio_track_init             ()
{
    MB::MBAudioTrack * audioTrack = new  MB::MBAudioTrack();
    return (void *)audioTrack;
}

int             mb_c_audio_track_uninit           (void * _audio_track)
{
    MB::MBAudioTrack * audioTrack = (MB::MBAudioTrack *)_audio_track;
    if(audioTrack != NULL){
        delete audioTrack;
    }
    return 0;
}

int             mb_c_audio_track_add_layer        (void * _audio_track, void * _layer)
{
    MB::MBAudioTrack * audioTrack = (MB::MBAudioTrack *)_audio_track;
    MB::MBAudioLayer * audioLayer = (MB::MBAudioLayer *)_layer;
    audioTrack->AddLayer(*audioLayer);
}

void *          mb_c_audio_layer_init             (double _startTime, double _endTime)
{
    MB::MBAudioLayer * audioLayer = new MB::MBAudioLayer();
    audioLayer->SetTime(_startTime, _endTime);
    return (void *)audioLayer;
}

int             mb_c_audio_layer_uninit           (void * _audio_layer)
{
    MB::MBAudioLayer * audioLayer = (MB::MBAudioLayer *)_audio_layer;
    if(audioLayer != NULL){
        delete audioLayer;
    }
    return 0;
}

int             mb_c_audio_layer_add_fragment     (void * _audio_layer, void * _audio_fragment)
{
    MB::MBAudioLayer * audioLayer = (MB::MBAudioLayer *)_audio_layer;
    MB::MBAudioFragment * audioFragment = (MB::MBAudioFragment *)_audio_fragment;
    audioLayer->AddAudioFragment(*audioFragment);
}

void *          mb_c_audio_fragment_init          (const char * _out_path)
{
    MB::MBAudioFragment * audioFragment = new MB::MBAudioFragment();
    audioFragment->LoadAudioFile(_out_path);
    return (void *)audioFragment;
}

int             mb_c_audio_fragment_uninit        (void * _audio_fragment)
{
    MB::MBAudioFragment * audioFragment = (MB::MBAudioFragment *)_audio_fragment;
    if(audioFragment != NULL){
        delete audioFragment;
    }
    return 0;
}

void *          mb_c_text_fragment_init          (const char * _out_path, char * text)
{
    MB::MBVideoFragmentText * fragmentText = new MB::MBVideoFragmentText();
    fragmentText->SetFontPath(_out_path);
    fragmentText->SetText(text);
    return (void *)fragmentText;
}

int             mb_c_text_fragment_uninit        (void * _text_fragment)
{
    MB::MBVideoFragmentText * fragmentText = (MB::MBVideoFragmentText *)_text_fragment;
    if(fragmentText != NULL){
        delete fragmentText;
    }
    return 0;
}

int             mb_c_text_fragment_style         (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width)
{
    MB::MBVideoFragmentText * videoFragmentText = (MB::MBVideoFragmentText *)_text_fragment;
    videoFragmentText->SetSize(size);
    videoFragmentText->SetColor(r, g, b);
    int width = videoFragmentText->GetTextWidth();
    if(x < 0){
        videoFragmentText->SetPos(video_width / 2.0 - width / 2.0, y);
    }else{
        videoFragmentText->SetPos(x, y);
    }
    return 0;
}

int             mb_c_layer_add_text_fragment     (void * _layer, void * _fragment)
{
    MB::MBVideoLayer * layer = (MB::MBVideoLayer *)_layer;
    MB::MBVideoFragmentText * fragment = (MB::MBVideoFragmentText *)_fragment;
    return layer->AddVideoFragment(fragment);
}

int             mb_c_fragment_add_filter          (void * _fragment, double t, int filterId, int level)
{
    MB::MBVideoFragmentVideo * fragment = (MB::MBVideoFragmentVideo *)_fragment;
    return fragment->AddFilterKey(t, filterId, level);
}

int             mb_c_text_fragment_width         (void * _text_fragment)
{
    MB::MBVideoFragmentText * videoFragmentText = (MB::MBVideoFragmentText *)_text_fragment;
    return videoFragmentText->GetTextWidth();
}

int             mb_c_text_fragment_size          (void * _text_fragment, int size)
{
    MB::MBVideoFragmentText * videoFragmentText = (MB::MBVideoFragmentText *)_text_fragment;
    return videoFragmentText->SetSize(size);
}

int             mb_c_audio_fragment_set_weight    (void * _audio_fragment, float _weight)
{
    MB::MBAudioFragment * audioFragment = (MB::MBAudioFragment *)_audio_fragment;
    return audioFragment->SetWeight(_weight);
}

void *          mb_c_frame_sequence_fragment_init   (const char * _path, int fileNum, int model)
{
    MB::MBVideoFragmentFrameSequential * fragmentFrameSequential = new MB::MBVideoFragmentFrameSequential();
    fragmentFrameSequential->SetDirPathModel(_path, fileNum, model);
    return (void *)fragmentFrameSequential;
}

int             mb_c_frame_sequence_fragment_uninit (void * _frame_sequence_fragment)
{
    MB::MBVideoFragmentFrameSequential * fragmentFrameSequential =(MB::MBVideoFragmentFrameSequential *)_frame_sequence_fragment;
    if(fragmentFrameSequential != NULL){
        delete fragmentFrameSequential;
    }
    return 0;
}

int             mb_c_frame_sequence_fragment_scale  (void * _frame_sequence_fragment, float _scaleX, float _scaleY, float _scaleZ)
{
    MB::MBVideoFragmentFrameSequential * fragmentFrameSequential =(MB::MBVideoFragmentFrameSequential *)_frame_sequence_fragment;
    return fragmentFrameSequential->SetScale(_scaleX, _scaleY, _scaleZ);
}

int             mb_c_frame_sequence_fragment_trans  (void * _frame_sequence_fragment, float _x, float _y, float _z)
{
    MB::MBVideoFragmentFrameSequential * fragmentFrameSequential =(MB::MBVideoFragmentFrameSequential *)_frame_sequence_fragment;
    return fragmentFrameSequential->SetTrans(_x, _y, _z);
}



