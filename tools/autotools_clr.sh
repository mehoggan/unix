#!/bin/bash

array=(rm -rf autom4te.cache/ config.h.in ./configure COPYING depcomp \
  INSTALL ltmain.sh ./config.guess config.sub aclocal.m4 ./m4/ ./test-driver \
  compile install-sh missing Makefile.in config.h config.log config.status \
  libtool Makefile stamp-h1 ar-lib $(find . -name Makefile.in))

for i in ${array[@]}; do
  rm -rf ${i};
done

