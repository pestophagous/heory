!android {
  QMAKE_CXXFLAGS += -isystem $${top_builddir}/fsynth_for_desktop/gcc_64/usr/local/include
}

android {
  x86 {
    QMAKE_CXXFLAGS += -isystem $${top_srcdir}/build/build_fsynth_for_android/x86/include/
  } else: armeabi-v7a {
    QMAKE_CXXFLAGS += -isystem $${top_srcdir}/build/build_fsynth_for_android/armeabi-v7a/include/
  } else: x86_64 {
    QMAKE_CXXFLAGS += -isystem $${top_srcdir}/build/build_fsynth_for_android/x86_64/include/
  } else: arm64-v8a {
    QMAKE_CXXFLAGS += -isystem $${top_srcdir}/build/build_fsynth_for_android/arm64-v8a/include/
  }
}

!include(fluidsynth_linkonly.pri) { error() }
