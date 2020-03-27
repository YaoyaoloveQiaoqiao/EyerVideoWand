#include "InterfaceCSharp.h"
#include "InterfaceC.h"

#include "EyerCore/EyerCore.hpp"

int mb_csharp_test_add(int a, int b)
{
    return eyer_wand_c_test_add(a, b);
}

int     mb_csharp_get_version                    (char * str_buf)
{
    return eyer_wand_c_get_version(str_buf);
}

void *  mb_csharp_builder_init                   (const char * out_path, int width, int height, int fps)
{
    return eyer_wand_c_builder_init(out_path, width, height, fps);
}

int     mb_csharp_builder_uninit                 (void * builder)
{
    return eyer_wand_c_builder_uninit(builder);
}

int     mb_csharp_builder_add_video_track             (void * builder, void * video_track)
{
    return eyer_wand_c_builder_add_video_track(builder, video_track);
}

int     mb_csharp_builder_add_audio_track        (void * builder, void * audio_track)
{
    return eyer_wand_c_builder_add_audio_track(builder, audio_track);
}


int     mb_csharp_builder_process                     (void * builder)
{
    return eyer_wand_c_builder_process(builder);
}

void *  mb_csharp_video_track_init                    ()
{
    return eyer_wand_c_video_track_init();
}

int     mb_csharp_video_track_uninit                  (void * video_track)
{
    return eyer_wand_c_video_track_uninit(video_track);
}

int     mb_csharp_video_track_add_layer               (void * _video_track, void * _layer)
{
    return eyer_wand_c_video_track_add_layer(_video_track, _layer);
}

void *  mb_csharp_layer_init                          (int _startFrameIndex, int _endFrameIndex)
{
    return eyer_wand_c_layer_init(_startFrameIndex, _endFrameIndex);
}

int     mb_csharp_layer_uninit                        (void * layer)
{
    return eyer_wand_c_layer_uninit(layer);
}

int     mb_csharp_layer_add_fragment                  (void * _layer, void * _fragment)
{
    return eyer_wand_c_layer_add_fragment(_layer, _fragment);
}

void *  mb_csharp_fragment_init                       (const char * _out_path)
{
    return eyer_wand_c_fragment_init(_out_path);
}

int     mb_csharp_fragment_uninit                     (void * _fragment)
{
    return eyer_wand_c_fragment_uninit(_fragment);
}

int     mb_csharp_fragment_add_transkey          (void * _fragment, double t, float x, float y, float z)
{
    return eyer_wand_c_fragment_add_transkey(_fragment, t, x, y, z);
}

int     mb_csharp_fragment_add_scalekey          (void * _fragment, double t, float x, float y, float z)
{
    return eyer_wand_c_fragment_add_scalekey(_fragment, t, x, y, z);
}

void *  mb_csharp_audio_track_init               ()
{
    return eyer_wand_c_audio_track_init();
}

int     mb_csharp_audio_track_uninit             (void * audio_track)
{
    return eyer_wand_c_audio_track_uninit(audio_track);
}

int     mb_csharp_audio_track_add_layer          (void * _audio_track, void * _layer)
{
    return eyer_wand_c_audio_track_add_layer(_audio_track, _layer);
}

void *  mb_csharp_audio_layer_init               (double _startTime, double _endTime)
{
    return eyer_wand_c_audio_layer_init(_startTime, _endTime);
}

int     mb_csharp_audio_layer_uninit             (void * _audio_layer)
{
    return eyer_wand_c_audio_layer_uninit(_audio_layer);
}

int     mb_csharp_audio_layer_add_fragment       (void * _audio_layer, void * _audio_fragment)
{
    return eyer_wand_c_audio_layer_add_fragment(_audio_layer, _audio_fragment);
}

void *  mb_csharp_audio_fragment_init            (const char * _out_path)
{
    return eyer_wand_c_audio_fragment_init(_out_path);
}

int     mb_csharp_audio_fragment_uninit          (void * _audio_fragment)
{
    return eyer_wand_c_audio_fragment_uninit(_audio_fragment);
}

void *  mb_csharp_text_fragment_init             (const char * _out_path, char * text)
{
    return eyer_wand_c_text_fragment_init(_out_path, text);
}

int     mb_csharp_text_fragment_uninit           (void * _text_fragment)
{
    return eyer_wand_c_text_fragment_uninit(_text_fragment);
}

int     mb_csharp_text_fragment_style            (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width)
{
    return eyer_wand_c_text_fragment_style(_text_fragment, size, x, y, r, g, b, video_width);
}

int     mb_csharp_layer_add_text_fragment        (void * _layer, void * _fragment)
{
    return eyer_wand_c_layer_add_text_fragment(_layer, _fragment);
}

