TESTS = check_image_processing
check_PROGRAMS = check_image_processing

check_image_processing_SOURCES = \
	check_image_processing.c \
	image_processing.h \
	utils.h

check_image_processing_CFLAGS = @CHECK_CFLAGS@

check_image_processing_LDADD = \
	$(top_builddir)/src/libimage_processing.la \
	@CHECK_LIBS@ \
	-lm \
	-lrt

check_image_processing_LDFLAGS = \
  -pthread

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/
