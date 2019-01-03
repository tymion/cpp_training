include(ExternalProject)

if (${CROSS_COMPILE})
    set(QEMU_ARGS --disable-bsd-user --disable-guest-agent --disable-strip --disable-werror --disable-gcrypt --disable-debug-info --disable-debug-tcg --disable-tcg-interpreter --enable-attr --disable-brlapi --disable-linux-aio --disable-bzip2 --disable-bluez --disable-cap-ng --disable-curl --disable-fdt --disable-glusterfs --disable-gnutls --disable-nettle --disable-gtk --disable-rdma --disable-libiscsi --disable-vnc-jpeg --disable-kvm --disable-lzo --disable-curses --disable-libnfs --disable-numa --disable-opengl --disable-vnc-png --disable-rbd --disable-vnc-sasl --disable-sdl --disable-seccomp --disable-smartcard --disable-snappy --disable-spice --disable-libssh2 --disable-libusb --disable-usb-redir --disable-vde --disable-vhost-net --disable-virglrenderer --disable-virtfs --disable-vnc --disable-vte --disable-xen --disable-xen-pci-passthrough --disable-xfsctl --enable-linux-user --disable-system --disable-blobs --disable-tools --target-list=arm-linux-user --static --disable-pie)

    ExternalProject_Add(
        qemu_target
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qemu
        DOWNLOAD_COMMAND ""
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/qemu/configure --prefix=${ROOTFS} ${QEMU_ARGS}
        )
endif ()

ExternalProject_Add(
    zlib_target
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib ${CMAKE_CURRENT_SOURCE_DIR}/zlib/configure --prefix=${ROOTFS}
    )

ExternalProject_Add(
    libpng_target
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libpng
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libpng/configure --prefix=${ROOTFS} CC=${CROSS_COMPILE}gcc AR=${CROSS_COMPILE}ar STRIP=${CROSS_COMPILE}strip RANLIB=${CROSS_COMPILE}ranlib CPPFLAGS=-I${ROOTFS}/include LDFLAGS=-L${ROOTFS}/lib/
    )

add_dependencies(libpng_target zlib_target)

ExternalProject_Add(
    gtest_target
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_ARGS
    "-DCROSS_COMPILE=${CROSS_COMPILE}"
    "-DCROSS_COMPILE_PATH=${CROSS_COMPILE_PATH}"
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    INSTALL_COMMAND make DESTDIR=${ROOTFS} install
    )
