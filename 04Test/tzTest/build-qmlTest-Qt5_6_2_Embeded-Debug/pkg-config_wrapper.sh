#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/opt/fsl-imx-x11/4.1.15-2.0.1/sysroots/cortexa9hf-neon-poky-linux-gnueabi
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/opt/fsl-imx-x11/4.1.15-2.0.1/sysroots/cortexa9hf-neon-poky-linux-gnueabi/usr/lib/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
