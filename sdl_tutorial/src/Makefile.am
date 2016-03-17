#lib_LTLIBRARIES = libsdl_tutorial.la
#libsdl_tutorial_la_SOURCES = \
#	jump_table.h jump_table.c \
#	opengl_core.h opengl_core.c \
#	my_dynap.c

bin_PROGRAMS = main
main_SOURCES = main.c
#main_LDADD = libsdl_tutorial.la
main_LDFLAGS = \
	-L$(SDL_DEBUG_LIB_PATH_ROOT)/build/.libs -l:libSDL2-2.0.so.0.4.0
main_CFLAGS = \
	-I$(SDL_DEBUG_LIB_PATH_ROOT)/include

CLEANFILES = *.o

