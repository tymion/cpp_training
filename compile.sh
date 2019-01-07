#!/bin/sh

CURR_PWD=$PWD
BUILD_PATH=build
TOOLCHAIN_FILE=$PWD/toolchain.cmake
DESTDIR_HOST=$CURR_PWD/$BUILD_PATH/rootfs-host
NPROC=$(nproc)
COMPILER_VERSION=$(gcc -v 2>&1 | grep "gcc version" | cut -c 13-17)
HOST=
DESTDIR_TARGET=

if [ "$COMPILER_VERSION" \> "7.0.0" ]; then
    echo "Host compiler is greater version than 7. It supports C++17. There's no need to use toolchain."
    HOST=x86_64
    DESTDIR_TARGET=$DESTDIR_HOST
else
    echo "Host compiler version is $COMPILER_VERSION. It doesn't supports C++17. Try to use toolchain."
    CROSS_COMPILE_PATH=$RT_OPENSRC_PATH/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/
    CROSS_COMPILE=$CROSS_COMPILE_PATH/bin/arm-linux-gnueabi-
    HOST=arm-linux-gnueabi
    DESTDIR_TARGET=$CURR_PWD/$BUILD_PATH/rootfs-target
fi

if [ "$NPROC" != "" ]; then
    export MAKEFLAGS=-j$NPROC
fi

create_rootfs() {
    if [ ! -d $1 ]; then
        mkdir -p $1/bin
        mkdir -p $1/sbin
        mkdir -p $1/include
        mkdir -p $1/lib
        mkdir -p $1/share
    fi
}

create_rootfs $DESTDIR_HOST
create_rootfs $DESTDIR_TARGET

cd $BUILD_PATH/

cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCROSS_COMPILE_PATH=$CROSS_COMPILE_PATH -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$DESTDIR_TARGET -DROOTFS_HOST=$DESTDIR_HOST -DHOST=$HOST
make
make DESTDIR=$DESTDIR_TARGET install

export LD_LIBRARY_PATH=$DESTDIR/lib:$DESTDIR/usr/local/lib
export QEMU_LD_PREFIX="$CROSS_COMPILE_PATH/$HOST/libc/"
export PATH=$PATH:$DESTDIR/bin:$DESTDIR/usr/local/bin
