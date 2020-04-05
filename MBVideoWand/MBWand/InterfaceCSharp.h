#include <stdio.h>

extern "C"
{
    #define EYER_DLLMODLE_FUNCTIONTYPE __declspec(dllexport)

    /* 测试，计算加法 */
    int     mb_csharp_test_add                       (int a, int b);

    int     mb_csharp_get_version                    (char * str_buf);



    void *  mb_csharp_builder_init                   (const char * out_path, int width, int height, int fps);
    int     mb_csharp_builder_uninit                 (void * builder);
    int     mb_csharp_builder_add_video_track        (void * builder, void * video_track);
    int     mb_csharp_builder_process                (void * builder);
    int     mb_csharp_builder_add_audio_track        (void * builder, void * audio_track);

    void *  mb_csharp_video_track_init               ();
    int     mb_csharp_video_track_uninit             (void * video_track);
    int     mb_csharp_video_track_add_layer          (void * _video_track, void * _layer);

    void *  mb_csharp_layer_init                     (int _startFrameIndex, int _endFrameIndex);
    int     mb_csharp_layer_uninit                   (void * layer);
    int     mb_csharp_layer_add_fragment             (void * _layer, void * _fragment);

    void *  mb_csharp_fragment_init                  (const char * _out_path);
    int     mb_csharp_fragment_uninit                (void * _fragment);
    
    int     mb_csharp_fragment_add_transkey          (void * _fragment, double t, float x, float y, float z);
    int     mb_csharp_fragment_add_scalekey          (void * _fragment, double t, float x, float y, float z);
    int     mb_csharp_fragment_add_filter            (void * _fragment, double t, int filterId, int level);

    void *  mb_csharp_audio_track_init               ();
    int     mb_csharp_audio_track_uninit             (void * audio_track);
    int     mb_csharp_audio_track_add_layer          (void * _audio_track, void * _layer);

    void *  mb_csharp_audio_layer_init               (double _startTime, double _endTime);
    int     mb_csharp_audio_layer_uninit             (void * _audio_layer);
    int     mb_csharp_audio_layer_add_fragment       (void * _audio_layer, void * _audio_fragment);

    void *  mb_csharp_audio_fragment_init            (const char * _out_path);
    int     mb_csharp_audio_fragment_uninit          (void * _audio_fragment);

    void *  mb_csharp_text_fragment_init             (const char * _out_path, char * text);
    int     mb_csharp_text_fragment_uninit           (void * _text_fragment);
    int     mb_csharp_text_fragment_style            (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width);
    int     mb_csharp_layer_add_text_fragment        (void * _layer, void * _fragment);
    int     mb_csharp_text_fragment_width            (void * _text_fragment);
    int     mb_csharp_text_fragment_size             (void * _text_fragment, int size);

}