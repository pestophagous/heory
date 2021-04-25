#if defined( ANDROID )

#    include <android/log.h>
#    include <jni.h>

// https://www.kdab.com/qt-android-episode-5/
static void handleIncomingMidi( JNIEnv* /*env*/, jobject /*obj*/, jint n )
{
    __android_log_print(
        ANDROID_LOG_INFO, "sometag", "MyAppActivity: (native) handleIncomingMidi" );
}

// Tip: use javap to find/confirm correct signatures. Like so:
//   javap -s classes/com/mycompany/myapp/MyJavaNatives.class
static JNINativeMethod ourJNINativeMethods[] = {{
    "onIncomingMidi", // const char* function name;
    "(I)V", // const char* function signature
    (void*) handleIncomingMidi // function pointer
}};

// JNI_OnLoad (once per .so file in any .cc) this method is called automatically
// by Java VM after the .so file is loaded
JNIEXPORT jint JNI_OnLoad( JavaVM* vm, void* /*reserved*/ )
{
    JNIEnv* env;
    if( vm->GetEnv( reinterpret_cast<void**>( &env ), JNI_VERSION_1_6 ) != JNI_OK )
    {
        return JNI_ERR;
    }

    jclass javaClass = env->FindClass( "com/mycompany/myapp/MyJavaNatives" );
    if( !javaClass )
        return JNI_ERR;

    if( env->RegisterNatives( javaClass, ourJNINativeMethods,
            sizeof( ourJNINativeMethods ) / sizeof( ourJNINativeMethods[ 0 ] ) )
        < 0 )
    {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

#endif // #if defined( ANDROID )
