lib_LTLIBRARIES = libfile_system.la
libfile_system_la_SOURCES = \
	filename.c \
	filename.h

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libfile_system.la

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/
