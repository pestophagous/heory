
# This 'pri' file can be used by the executable, which needs to link against
# fluidsynth but NOT be able to 'see' the header files.
#
# In other words, here we put libfluidsynth on linker path but >NOT< include path!

LIBS += -L$${top_builddir}/fsynth/gcc_64/usr/local/lib64 -lfluidsynth
