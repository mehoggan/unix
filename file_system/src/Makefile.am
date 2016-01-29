lib_LTLIBRARIES = libfile_system.la
libfile_system_la_SOURCES = \
	file_name.c \
	file_name.h \
	path_name.c \
	path_name.h

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libfile_system.la

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/
