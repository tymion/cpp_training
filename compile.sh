#!/bin/sh

CURR_PWD=$PWD
LIB_DIR=$PWD/libraries
BUILD_PATH=build
TOOLCHAIN_FILE=toolchain.cmake
SYSROOT=$CURR_PWD/$BUILD_PATH/rootfs
CROSS_COMPILE=$RT_OPENSRC_PATH/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-

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
    CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib $LIB_DIR/zlib/configure --prefix=$CURR_PWD/$BUILD_PATH/rootfs
fi
make
make install
cd ../

cd libpng
if [ ! -f Makefile ]; then
    $LIB_DIR/libpng/configure --prefix=$CURR_PWD/$BUILD_PATH/rootfs --host=arm-linux-gnueabi CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib CPPFLAGS="-I$CURR_PWD/$BUILD_PATH/rootfs/include" LDFLAGS="-L$CURR_PWD/$BUILD_PATH/rootfs/lib/"
fi
make
make install
cd ../

cd gtest
make -C $LIB_DIR/gtest/googlemock/make/
cp -rf $LIB_DIR/gtest/googletest/include/* ../rootfs/include
cd ../

#cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DSYSROOT=$SYSROOT -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE
cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$CURR_PWD/$BUILD_PATH/rootfs/
make
cd -
