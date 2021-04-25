#if defined( ANDROID )

#    include <android/log.h>
#    include <jni.h>

namespace
{
unsigned char* as_unsigned_char_array( JNIEnv* env, jbyteArray array )
{
    int len = env->GetArrayLength( array );
    unsigned char* buf = new unsigned char[ len ];
    env->GetByteArrayRegion( array, 0, len, reinterpret_cast<jbyte*>( buf ) );
    return buf;
}
} // namespace

// https://www.kdab.com/qt-android-episode-5/
static void handleIncomingMidi(
    JNIEnv* env, jobject /*obj*/, jbyteArray value, const jint offset, const jint count )
{
    // __android_log_print(
    //     ANDROID_LOG_INFO, "sometag", "MyAppActivity: (native) handleIncomingMidi" );

    fluid_midi_parser_t* parser = new_fluid_midi_parser();
    fluid_midi_event_t* evt = nullptr;
    unsigned char* incomingString = as_unsigned_char_array( env, value );
    unsigned char* iter = incomingString + offset;

    for( int i = 0; i < count; i++ )
    {
        unsigned char theChar = ( *iter );

        /*
          Event is internal and should not be modified or freed and is only valid
          until next call to fluid_midi_parser_parse.
        */
        evt = fluid_midi_parser_parse( parser, theChar );

        // __android_log_print( ANDROID_LOG_INFO, "sometag",
        //     "MyAppActivity: sending to parser %d of %d 0x%02X", i, static_cast<int>( count
        //     ), theChar );

        if( evt )
        {
            heory::OnIncomingMidiEvent( g_preRouter, evt );
        }
        iter++;
    }

    delete_fluid_midi_parser( parser );
    delete[] incomingString;
}

// Tip: use javap to find/confirm correct signatures. Like so:
//   javap -s classes/com/mycompany/myapp/MyJavaNatives.class
static JNINativeMethod ourJNINativeMethods[] = {{
    "onIncomingMidi", // const char* function name;
    "([BII)V", // const char* function signature
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
