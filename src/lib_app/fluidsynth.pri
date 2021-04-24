!android {
  QMAKE_CXXFLAGS += -isystem $${top_builddir}/fsynth/gcc_64/usr/local/include
}

android {
  # TODO-ANDROID (should this use the gcc_64 header? probably not...)
  QMAKE_CXXFLAGS += -isystem $${top_srcdir}/build/fsynth/gcc_64/usr/local/include
}

!include(fluidsynth_linkonly.pri) { error() }
