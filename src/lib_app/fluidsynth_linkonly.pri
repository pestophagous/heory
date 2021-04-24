
# This 'pri' file can be used by the executable, which needs to link against
# fluidsynth but NOT be able to 'see' the header files.
#
# In other words, here we put libfluidsynth on linker path but >NOT< include path!

!android {
  LIBS += -L$${top_builddir}/fsynth/gcc_64/usr/local/lib64 -lfluidsynth
}

android {

  x86 {
    andarchfolder = $$PWD/../../fluidsynth/build/x86
  } else: armeabi-v7a {
    andarchfolder = $$PWD/../../fluidsynth/build/armeabi-v7a
  } else: x86_64 {
    andarchfolder = $$PWD/../../fluidsynth/build/x86_64
  } else: arm64-v8a {
    andarchfolder = $$PWD/../../fluidsynth/build/arm64-v8a
  }

  LIBS += -L$${andarchfolder} -lfluidsynth

  # Docs suggest a one-liner this. https://doc.qt.io/qt-5/qmake-variable-reference.html#android-extra-libs
  # I could not make the one-liner generate the desired outcome!
  #    for (abi, ANDROID_ABIS): ANDROID_EXTRA_LIBS += $$PWD/$${abi}/library_name.so
  ANDROID_EXTRA_LIBS += $$PWD/../../fluidsynth/build/x86/libfluidsynth.so \
    $$PWD/../../fluidsynth/build/armeabi-v7a/libfluidsynth.so \
    $$PWD/../../fluidsynth/build/x86_64/libfluidsynth.so \
    $$PWD/../../fluidsynth/build/arm64-v8a/libfluidsynth.so

}