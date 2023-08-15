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
    mkdir -p ./example
    $CC $FLAGS $INCLUDE -shared -fPIC $FILES -o ./example/libccp.so
    $CC -Wl,-rpath ./example -lccp -L ./example $FLAGS $INCLUDE -o ./example/a.out ./example.c
}


function clean() {
    rm -rf ./example
    rm -rf ./build
}

if [[ "$1" == "-b" ]]; then
    make_lib
elif [[ "$1" == "-e" ]]; then
    compile_example
elif [[ "$1" == "-c" ]]; then
    clean
fi

