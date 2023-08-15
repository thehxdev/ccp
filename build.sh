#!/usr/bin/env bash

set -xe

CC="gcc"
FLAGS="-std=c17 -Wall -Wextra -O2 "
FLAGS+="-Werror -Wno-unused-result -Wno-unused-variable -Wno-unused-parameter "
INCLUDE="-I./lib"

FILES="./lib/ccp/*.c ./lib/ccp/utils/*.c"

function make_lib() {
    local outdir="./build"
    mkdir -p $outdir
    $CC $FLAGS $INCLUDE -shared -fPIC $FILES -o $outdir/libccp.so

    cp -r ./lib/ccp ./build/
    rm -rf ./build/ccp/*.c ./build/ccp/utils/*.c
}

function compile_example() {
    $CC -Wl,-rpath ./shared -lccp -L ./shared $FLAGS $INCLUDE ./main.c
}

make_lib
#compile
