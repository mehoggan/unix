TESTS = check_file_system
check_PROGRAMS = check_file_system
check_file_system_SOURCES = \
	check_file_name.c \
	check_path_name.c \
	$(top_builddir)/src/file_name.h \
	$(top_builddir)/src/path_name.h
check_file_system_CFLAGS = @CHECK_CFLAGS@
check_file_system_LDADD = \
	$(top_builddir)/src/libfile_sytem.la \
	@CHECK_LIBS@
