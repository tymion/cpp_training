#!/bin/sh

PWD=pwd
BUILD_PATH=build
TOOLCHAIN_FILE=toolchain.cmake
SYSROOT=$PWD/$BUILD_PATH/rootfs
CROSS_COMPILE=$HOME/Data/OpenSource/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-

if [ ! -d $BUILD_PATH ]; then
    mkdir -p $BUILD_PATH/rootfs/bin
    mkdir -p $BUILD_PATH/rootfs/include
    mkdir -p $BUILD_PATH/rootfs/lib
    mkdir -p $BUILD_PATH/rootfs/share
    mkdir -p $BUILD_PATH/libpng
fi

cd $BUILD_PATH/libpng
./../../libraries/libpng/configure --prefix=$PWD/build/rootfs
make
make install
cd ../

#cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DSYSROOT=$SYSROOT -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE
cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE
make
cd -
