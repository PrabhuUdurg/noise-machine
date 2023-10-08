#!/bin/sh 

set -xe

CFALGS="-Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --cflags raylib`"

clang++ $CFLAGS -o noise main.cpp -lraylib -lsndfile
