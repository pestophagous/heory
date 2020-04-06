
QMAKE_CXXFLAGS += -isystem $${top_builddir}/fsynth/gcc_64/usr/local/include

!include(fluidsynth_linkonly.pri) { error() }
