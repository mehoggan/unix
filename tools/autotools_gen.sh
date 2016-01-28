#!/bin/bash

aclocal && autoconf && autoreconf --no-recursive --install && \
    autoheader && libtoolize --force && automake --force-missing \
    --add-missing
