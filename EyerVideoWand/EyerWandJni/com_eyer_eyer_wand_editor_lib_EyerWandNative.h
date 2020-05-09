/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_eyer_eyer_wand_editor_lib_EyerWandNative */

#ifndef _Included_com_eyer_eyer_wand_editor_lib_EyerWandNative
#define _Included_com_eyer_eyer_wand_editor_lib_EyerWandNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    get_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_get_1version
  (JNIEnv *, jclass);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    crop_init
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1init
  (JNIEnv *, jclass, jint, jint, jint, jint);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    crop_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    crop_get_crop_width
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1get_1crop_1width
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    crop_get_crop_height
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1get_1crop_1height
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    crop_crop
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_crop_1crop
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    ogl_create_thread
 * Signature: (Landroid/view/Surface;)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1create_1thread
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    ogl_stop_thread
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1stop_1thread
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    ogl_set_wh
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1set_1wh
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    ogl_add_task_to_render_queue
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1add_1task_1to_1render_1queue
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    ogl_add_task_to_destory_queue
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_ogl_1add_1task_1to_1destory_1queue
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    render_task_init
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_render_1task_1init
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    render_task_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_render_1task_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    avreader_init
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1init
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    avreader_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    avreader_open
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1open
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    avreader_close
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1close
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    avreader_print_info
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_avreader_1print_1info
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_context_init
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1init
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_context_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_context_set_gl_ctx
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1set_1gl_1ctx
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_context_render_frame
 * Signature: (JD)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1context_1render_1frame
  (JNIEnv *, jclass, jlong, jdouble);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_snapshot_init
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1init
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_snapshot_uninit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1uninit
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_eyer_eyer_wand_editor_lib_EyerWandNative
 * Method:    wand_snapshot_bitmap
 * Signature: (JDLandroid/graphics/Bitmap;)I
 */
JNIEXPORT jint JNICALL Java_com_eyer_eyer_1wand_1editor_1lib_EyerWandNative_wand_1snapshot_1bitmap
  (JNIEnv *, jclass, jlong, jdouble, jobject);

#ifdef __cplusplus
}
#endif
#endif
