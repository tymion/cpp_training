#!/bin/sh

CURR_PWD=$PWD
LIB_DIR=$PWD/libraries
BUILD_PATH=build
TOOLCHAIN_FILE=toolchain.cmake
SYSROOT=$CURR_PWD/$BUILD_PATH/rootfs
CROSS_COMPILE=$HOME/Data/OpenSource/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-

if [ ! -d $BUILD_PATH ]; then
    mkdir -p $BUILD_PATH/rootfs/bin
    mkdir -p $BUILD_PATH/rootfs/include
    mkdir -p $BUILD_PATH/rootfs/lib
    mkdir -p $BUILD_PATH/rootfs/share
    mkdir -p $BUILD_PATH/libpng
    mkdir -p $BUILD_PATH/zlib
fi

cd $BUILD_PATH/zlib
CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib $LIB_DIR/zlib/configure --prefix=$CURR_PWD/$BUILD_PATH/rootfs
make
make install
cd ../

cd libpng
$LIB_DIR/libpng/configure --prefix=$CURR_PWD/$BUILD_PATH/rootfs --host=arm-linux-gnueabi CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib CPPFLAGS="-I$CURR_PWD/$BUILD_PATH/rootfs/include" LDFLAGS="-L$CURR_PWD/$BUILD_PATH/rootfs/lib/"
make
make install
cd ../

cd gtest/googletest
make -C make
cd ../

#cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DSYSROOT=$SYSROOT -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE
cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$CURR_PWD/$BUILD_PATH/rootfs/
make
cd -
