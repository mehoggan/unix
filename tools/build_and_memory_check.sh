#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Please pass in the library name (e.g. filesystem)."
  exit -1;
fi

../tools/autotools_clr.sh && ../tools/autotools_gen.sh && \
  export CFLAGS='-g -O0' && ./configure && make clean all check

export LD_LIBRARY_PATH=`pwd`/src/.libs/ && valgrind ./tests/.libs/check_${1}
