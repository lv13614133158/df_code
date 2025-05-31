#!/bin/bash
path=$( cd $( dirname " ${BASH_SOURCE[0]} " ) && pwd ) ##
echo $path


export TOOLCHAIN_DIR=/home/nvidia/df/HAD/S73a2/toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-aarch64-none-linux-gnu
export CMAKE_C_COMPILER=$TOOLCHAIN_DIR/bin/aarch64-none-linux-gnu-gcc
#export CMAKE_CXX_COMPILER=$TOOLCHAIN_DIR/bin/aarch64-none-linux-gnu-g++


# cd /home/toolchain/S73/TBOX/oecore-x86_64/ql-ol-crosstool
# # 设定环境，
# source ql-ol-crosstool-env-init
# 指定路径，make extsdk
#make extsdk -C /home/toolchain/WHDF/ 
#make extsdk 

mkdir -p $path/build
cd $path/build
rm -r *
cmake ..
make 

mkdir -p $path/output
rm -rf $path/output/*
mkdir $path/output/lib
mkdir $path/output/bin
mkdir $path/output/conf
mkdir $path/output/log
mkdir $path/output/conf/config/
mkdir -p $path/output/conf/config/

cp $path/build/IDPS $path/output/bin/
cp $path/script/IDPS_start.sh $path/output/bin/
cp $path/script/IDPS_stop.sh $path/output/bin/
cp $path/config/base_config.json $path/output/conf/config/
cp $path/config/policy_config.json $path/output/conf/config/
cp $path/config/device_info.conf $path/output/conf/config/

#test
$CMAKE_C_COMPILER $path/script/main_test.c -o $path/output/bin/main_test