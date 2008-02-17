#!/bin/sh
aclocal
libtoolize -f
automake -ca
autoconf
