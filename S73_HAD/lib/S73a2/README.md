# AppSDK 使用说明

使用说明：

1. AppSDK 包含头文件以及库文件，用于编译生成应用，生成的应用可在J6板端运行。

2. 工具链为 **gcc-12-aarch64-linux-gnu** 以及 **g++-12-aarch64-linux-gnu**，版本为**12.2.0-1ubuntu1~22.04cross1**，需自行安装，安装方法见《交叉编译工具链安装》章节。

文件说明：

1. ./appuser/rootfs-sdk*.deb：debian rootfs 头文件、库等

2. ./appuser/hbrootfs-sdk*.deb：hobot 自研 头文件、库等

解压方法：

1. dpkg-deb -x rootfs-sdk*.deb ./sdk

2. dpkg-deb -x hbrootfs-sdk*.deb ./sdk

解压后文件：

```bash
~/test/sdk# tree -d -L 2
    .
    ├── bin
    ├── etc
    │   ├── OpenCL
    │   ├── selinux
    │   └── vulkan
    ├── include
    │   ├── libavcodec
    │   ├── libavdevice
    │   ├── libavfilter
    │   ├── libavformat
    │   ├── libavutil
    │   ├── libswresample
    │   └── libswscale
    ├── lib
    │   └── systemd
    └── usr
        ├── bin
        ├── games
        ├── hobot # hbrootfs
        ├── include
        ├── lib
        ├── local
        ├── sbin
        ├── share
        └── src
```

其中，hbrootfs解压后的文件位于: ./usr/hobot

# 交叉编译工具链安装

开发环境版本要求: **ubuntu22.04**

交叉编译工具链安装：

```bash
apt install gcc-12-aarch64-linux-gnu=12.2.0-14cross1
apt install g++-12-aarch64-linux-gnu=12.2.0-14cross1
```

验证：

```bash
aarch64-linux-gnu-gcc --version

aarch64-linux-gnu-gcc (Debian 12.2.0-14) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
