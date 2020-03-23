#include <stdio.h>

extern "C"
{
    #define EYER_DLLMODLE_FUNCTIONTYPE __declspec(dllexport)

    /* 测试，计算加法 */
    int     eyer_wand_csharp_test_add                       (int a, int b);

    int     eyer_wand_csharp_get_version                    (char * str_buf);



    void *  eyer_wand_csharp_builder_init                   (const char * out_path, int width, int height, int fps);
    int     eyer_wand_csharp_builder_uninit                 (void * builder);
    int     eyer_wand_csharp_builder_add_video_track        (void * builder, void * video_track);
    int     eyer_wand_csharp_builder_process                (void * builder);

    void *  eyer_wand_csharp_video_track_init               ();
    int     eyer_wand_csharp_video_track_uninit             (void * video_track);
    int     eyer_wand_csharp_video_track_add_layer          (void * _video_track, void * _layer);

    void *  eyer_wand_csharp_layer_init                     (int _startFrameIndex, int _endFrameIndex);
    int     eyer_wand_csharp_layer_uninit                   (void * layer);
    int     eyer_wand_csharp_layer_add_fragment             (void * _layer, void * _fragment);

    void *  eyer_wand_csharp_fragment_init                  (const char * _out_path);
    int     eyer_wand_csharp_fragment_uninit                (void * _fragment);
}