

#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_edgeviewer_MainActivity_processImage(JNIEnv *env, jobject, jobject bitmapIn) {
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmapIn, &info);

    void* pixels;
    AndroidBitmap_lockPixels(env, bitmapIn, &pixels);

    Mat src(info.height, info.width, CV_8UC4, pixels);
    Mat gray, edges;

    // Convert to grayscale and detect edges
    cvtColor(src, gray, COLOR_RGBA2GRAY);
    GaussianBlur(gray, gray, Size(5,5), 1.5);
    Canny(gray, edges, 50, 150);

    // Convert back to RGBA for display
    Mat result;
    cvtColor(edges, result, COLOR_GRAY2RGBA);

    AndroidBitmap_unlockPixels(env, bitmapIn);

    // Create output Bitmap
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmap = env->GetStaticMethodID(
            bitmapCls, "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass configCls = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOf = env->GetStaticMethodID(configCls, "valueOf",
                                               "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
    jobject bitmapConfig = env->CallStaticObjectMethod(configCls, valueOf, configName);
    jobject bitmapOut = env->CallStaticObjectMethod(bitmapCls, createBitmap,
                                                    info.width, info.height, bitmapConfig);

    void* resultPixels;
    AndroidBitmap_lockPixels(env, bitmapOut, &resultPixels);
    memcpy(resultPixels, result.data, result.total() * result.elemSize());
    AndroidBitmap_unlockPixels(env, bitmapOut);

    return bitmapOut;
}
