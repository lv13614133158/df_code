#!/bin/bash
path=$( cd $( dirname " ${BASH_SOURCE[0]} " ) && pwd ) ##
echo $path


#cd /home/toolchain/WHDF5G-MKT
# 设定环境，
#source /home/toolchain/WHDF/config.rc
#source config.rc
# 指定路径，make extsdk
#make extsdk -C /home/toolchain/WHDF/ 
#make extsdk 
source /home/share/T106/esdk/environment-setup-armv7a-zxic-linux-gnueabi
export SYSROOT=/home/toolchain/DFT106/T106/esdk/tmp/sysroots/zx297520v3


cd $path/build
rm -r *

cmake ..

make

cp libspdlog.a ../lib
