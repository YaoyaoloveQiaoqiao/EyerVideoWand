#include <stdio.h>

extern "C"
{
    /* 获取 eyer_wand 的版本号 */
    int             eyer_wand_c_get_version                 (char * version);

    /* 测试，计算加法 */
    int             eyer_wand_c_test_add                    (int a, int b);

    void *          eyer_wand_c_builder_init                (const char * out_path, int width, int height, int fps);
    int             eyer_wand_c_builder_uninit              (void * builder);
    int             eyer_wand_c_builder_add_video_track     (void * builder, void * video_track);
    int             eyer_wand_c_builder_add_audio_track     (void * builder, void * audio_track);
    int             eyer_wand_c_builder_process             (void * builder);


    void *          eyer_wand_c_video_track_init            ();
    int             eyer_wand_c_video_track_uninit          (void * video_track);
    int             eyer_wand_c_video_track_add_layer(void * _video_track, void * _layer);

    void *          eyer_wand_c_layer_init                (int _startFrameIndex, int _endFrameIndex);
    int             eyer_wand_c_layer_uninit              (void * layer);
    int             eyer_wand_c_layer_add_fragment     (void * _layer, void * _fragment);

    void *          eyer_wand_c_fragment_init                (const char * _out_path);
    int             eyer_wand_c_fragment_uninit              (void * _fragment);
    int             eyer_wand_c_fragment_add_transkey        (void * _fragment, double t, float x, float y, float z);
    int             eyer_wand_c_fragment_add_scalekey        (void * _fragment, double t, float x, float y, float z);
    
    void *          eyer_wand_c_audio_track_init             ();
    int             eyer_wand_c_audio_track_uninit           (void * audio_track);
    int             eyer_wand_c_audio_track_add_layer        (void * _audio_track, void * _layer);

    void *          eyer_wand_c_audio_layer_init             (double _startTime, double _endTime);
    int             eyer_wand_c_audio_layer_uninit           (void * _audio_layer);
    int             eyer_wand_c_audio_layer_add_fragment     (void * _audio_layer, void * _audio_fragment);

    void *          eyer_wand_c_audio_fragment_init          (const char * _out_path);
    int             eyer_wand_c_audio_fragment_uninit        (void * _audio_fragment);

    void *          eyer_wand_c_text_fragment_init          (const char * _out_path, char * text);
    int             eyer_wand_c_text_fragment_uninit        (void * _text_fragment);
    int             eyer_wand_c_text_fragment_style         (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width);
    int             eyer_wand_c_layer_add_text_fragment     (void * _layer, void * _fragment);

}