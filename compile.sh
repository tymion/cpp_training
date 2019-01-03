#!/bin/sh

CURR_PWD=$PWD
LIB_DIR=$PWD/libs
BUILD_PATH=build
TOOLCHAIN_FILE=$PWD/toolchain.cmake
DESTDIR=$CURR_PWD/$BUILD_PATH/rootfs
COMPILER_VERSION=$(gcc -v 2>&1 | grep "gcc version" | cut -c 13-17)
HOST=
if [ "$COMPILER_VERSION" \> "7.0.0" ]; then
    echo "Host compiler is greater version than 7. It supports C++17. There's no need to use toolchain."
else
    echo "Host compiler version is $COMPILER_VERSION. It doesn't supports C++17. Try to use toolchain."
    CROSS_COMPILE_PATH=$RT_OPENSRC_PATH/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/
    CROSS_COMPILE=$CROSS_COMPILE_PATH/bin/arm-linux-gnueabi-
    HOST=arm-linux-gnueabi
fi

if [ ! -d $BUILD_PATH ]; then
    mkdir -p $BUILD_PATH/rootfs/bin
    mkdir -p $BUILD_PATH/rootfs/include
    mkdir -p $BUILD_PATH/rootfs/lib
    mkdir -p $BUILD_PATH/rootfs/share
    mkdir -p $BUILD_PATH/libpng
    mkdir -p $BUILD_PATH/zlib
    mkdir -p $BUILD_PATH/gtest
fi

cd $BUILD_PATH/zlib
if [ ! -f Makefile ]; then
    CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib $LIB_DIR/zlib/configure --prefix=$DESTDIR
fi
make
make install
cd ../

cd libpng
if [ ! -f Makefile ]; then
    $LIB_DIR/libpng/configure --prefix=$DESTDIR --host=$HOST CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib CPPFLAGS="-I$DESTDIR/include" LDFLAGS="-L$DESTDIR/lib/"
fi
make
make install
cd ../

cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCROSS_COMPILE_ROOT=$CROSS_COMPILE_PATH -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$DESTDIR
make
make DESTDIR=$DESTDIR install
