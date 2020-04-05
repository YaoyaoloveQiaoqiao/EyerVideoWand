#include <stdio.h>

extern "C"
{
    /* 获取 eyer_wand 的版本号 */
    int             mb_c_get_version                 (char * version);

    /* 测试，计算加法 */
    int             mb_c_test_add                    (int a, int b);

    void *          mb_c_builder_init                (const char * out_path, int width, int height, int fps);
    int             mb_c_builder_uninit              (void * builder);
    int             mb_c_builder_add_video_track     (void * builder, void * video_track);
    int             mb_c_builder_add_audio_track     (void * builder, void * audio_track);
    int             mb_c_builder_process             (void * builder);


    void *          mb_c_video_track_init            ();
    int             mb_c_video_track_uninit          (void * video_track);
    int             mb_c_video_track_add_layer(void * _video_track, void * _layer);

    void *          mb_c_layer_init                (int _startFrameIndex, int _endFrameIndex);
    int             mb_c_layer_uninit              (void * layer);
    int             mb_c_layer_add_fragment     (void * _layer, void * _fragment);

    void *          mb_c_fragment_init                (const char * _out_path);
    int             mb_c_fragment_uninit              (void * _fragment);
    int             mb_c_fragment_add_transkey        (void * _fragment, double t, float x, float y, float z);
    int             mb_c_fragment_add_scalekey        (void * _fragment, double t, float x, float y, float z);
    int             mb_c_fragment_add_filter          (void * _fragment, double t, int filterId, int level);

    void *          mb_c_audio_track_init             ();
    int             mb_c_audio_track_uninit           (void * audio_track);
    int             mb_c_audio_track_add_layer        (void * _audio_track, void * _layer);

    void *          mb_c_audio_layer_init             (double _startTime, double _endTime);
    int             mb_c_audio_layer_uninit           (void * _audio_layer);
    int             mb_c_audio_layer_add_fragment     (void * _audio_layer, void * _audio_fragment);

    void *          mb_c_audio_fragment_init          (const char * _out_path);
    int             mb_c_audio_fragment_uninit        (void * _audio_fragment);

    void *          mb_c_text_fragment_init          (const char * _out_path, char * text);
    int             mb_c_text_fragment_uninit        (void * _text_fragment);
    int             mb_c_text_fragment_style         (void * _text_fragment, int size,  float x, float y, float r, float g, float b, int video_width);
    int             mb_c_layer_add_text_fragment     (void * _layer, void * _fragment);
    int             mb_c_text_fragment_width         (void * _text_fragment);
    int             mb_c_text_fragment_size          (void * _text_fragment, int size);


}