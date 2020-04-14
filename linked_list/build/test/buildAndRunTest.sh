#! /bin/sh

gcc -o ./lltest -DUSE_COLOUR -I ../../include/ -I ../../../common/include/ ../../test/main.c ../../../common/src/Utils.c && ./lltest
