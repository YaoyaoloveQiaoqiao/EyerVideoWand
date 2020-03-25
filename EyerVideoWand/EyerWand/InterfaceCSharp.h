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
    
}