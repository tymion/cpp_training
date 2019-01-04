#!/bin/sh

CURR_PWD=$PWD
BUILD_PATH=build
TOOLCHAIN_FILE=$PWD/toolchain.cmake
DESTDIR=$CURR_PWD/$BUILD_PATH/rootfs
NPROC=$(nproc)
COMPILER_VERSION=$(gcc -v 2>&1 | grep "gcc version" | cut -c 13-17)
HOST=

if [ "$COMPILER_VERSION" \> "7.0.0" ]; then
    echo "Host compiler is greater version than 7. It supports C++17. There's no need to use toolchain."
    HOST=x86_64
else
    echo "Host compiler version is $COMPILER_VERSION. It doesn't supports C++17. Try to use toolchain."
    CROSS_COMPILE_PATH=$RT_OPENSRC_PATH/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/
    CROSS_COMPILE=$CROSS_COMPILE_PATH/bin/arm-linux-gnueabi-
    HOST=arm-linux-gnueabi
fi

if [ "$NPROC" != "" ]; then
    export MAKEFLAGS=-j$NPROC
fi

if [ ! -d $BUILD_PATH ]; then
    mkdir -p $BUILD_PATH/rootfs/bin
    mkdir -p $BUILD_PATH/rootfs/include
    mkdir -p $BUILD_PATH/rootfs/lib
    mkdir -p $BUILD_PATH/rootfs/share
    mkdir -p $BUILD_PATH/libpng
    mkdir -p $BUILD_PATH/zlib
    mkdir -p $BUILD_PATH/gtest
    mkdir -p $BUILD_PATH/qemu
fi

cd $BUILD_PATH/

cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCROSS_COMPILE_PATH=$CROSS_COMPILE_PATH -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$DESTDIR -DHOST=$HOST
make
make DESTDIR=$DESTDIR install

export LD_LIBRARY_PATH=$DESTDIR/lib:$DESTDIR/usr/local/lib
export QEMU_LD_PREFIX="$CROSS_COMPILE_PATH/$HOST/libc/"
export PATH=$PATH:$DESTDIR/bin:$DESTDIR/usr/local/bin
