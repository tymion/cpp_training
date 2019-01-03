#!/bin/sh

CURR_PWD=$PWD
LIB_DIR=$PWD/libs
BUILD_PATH=build
TOOLCHAIN_FILE=$PWD/toolchain.cmake
DESTDIR=$CURR_PWD/$BUILD_PATH/rootfs
NPROC=$(nproc)
COMPILER_VERSION=$(gcc -v 2>&1 | grep "gcc version" | cut -c 13-17)
HOST=
MAKEFILE_ARGS=
QEMU_ARGS="--disable-bsd-user --disable-guest-agent --disable-strip --disable-werror --disable-gcrypt --disable-debug-info --disable-debug-tcg --disable-tcg-interpreter --enable-attr --disable-brlapi --disable-linux-aio --disable-bzip2 --disable-bluez --disable-cap-ng --disable-curl --disable-fdt --disable-glusterfs --disable-gnutls --disable-nettle --disable-gtk --disable-rdma --disable-libiscsi --disable-vnc-jpeg --disable-kvm --disable-lzo --disable-curses --disable-libnfs --disable-numa --disable-opengl --disable-vnc-png --disable-rbd --disable-vnc-sasl --disable-sdl --disable-seccomp --disable-smartcard --disable-snappy --disable-spice --disable-libssh2 --disable-libusb --disable-usb-redir --disable-vde --disable-vhost-net --disable-virglrenderer --disable-virtfs --disable-vnc --disable-vte --disable-xen --disable-xen-pci-passthrough --disable-xfsctl --enable-linux-user --disable-system --disable-blobs --disable-tools --target-list=arm-linux-user --static --disable-pie"

if [ "$COMPILER_VERSION" \> "7.0.0" ]; then
    echo "Host compiler is greater version than 7. It supports C++17. There's no need to use toolchain."
else
    echo "Host compiler version is $COMPILER_VERSION. It doesn't supports C++17. Try to use toolchain."
    CROSS_COMPILE_PATH=$RT_OPENSRC_PATH/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/
    CROSS_COMPILE=$CROSS_COMPILE_PATH/bin/arm-linux-gnueabi-
    HOST=arm-linux-gnueabi
fi

if [ "$NPROC" != "" ]; then
    MAKEFILE_ARGS=-j$NPROC
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

if [ "$HOST" != "" ]; then
    cd qemu
    if [ ! -f Makefile ]; then
        $LIB_DIR/qemu/configure --prefix=$DESTDIR $QEMU_ARGS
    fi
    make $MAKEFILE_ARGS
    make install
    cd ../
fi

cd zlib
if [ ! -f Makefile ]; then
    CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib $LIB_DIR/zlib/configure --prefix=$DESTDIR
fi
make $MAKEFILE_ARGS
make install
cd ../

cd libpng
if [ ! -f Makefile ]; then
    $LIB_DIR/libpng/configure --prefix=$DESTDIR --host=$HOST CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib CPPFLAGS="-I$DESTDIR/include" LDFLAGS="-L$DESTDIR/lib/"
fi
make $MAKEFILE_ARGS
make install
cd ../

cmake ../ -DCROSS_COMPILE=$CROSS_COMPILE -DCROSS_COMPILE_PATH=$CROSS_COMPILE_PATH -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE -DROOTFS=$DESTDIR
make $MAKEFILE_ARGS
make DESTDIR=$DESTDIR install
