lib_LTLIBRARIES = libimage_processing.la
libimage_processing_la_SOURCES = \
	image_processing.c \
	image_processing.h \
	utils.c \
	utils.h

libimage_processing_la_LDFLAGS = \
	-lm

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libimage_processing.la

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/
