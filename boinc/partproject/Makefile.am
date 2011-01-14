## -*- mode: makefile; tab-width: 4 -*-


include $(top_srcdir)/Makefile.incl

partproject_output = $(libexecdir)/partproject
partproject_output_PROGRAMS = partproject

partproject_SOURCES = checkpoint.cpp file.cpp math.cpp partproject.cpp result.cpp
partproject_CXXFLAGS = $(PTHREAD_CFLAGS)
partproject_LDFLAGS = -static-libtool-libs $(PTHREAD_CFLAGS)
partproject_LDADD = $(APPLIBS)
