#!/bin/bash
path=$( cd $( dirname " ${BASH_SOURCE[0]} " ) && pwd ) ##
echo $path


cd /home/toolchain/S73/TBOX/oecore-x86_64/ql-ol-crosstool
# 设定环境，
source ql-ol-crosstool-env-init
# 指定路径，make extsdk
#make extsdk -C /home/toolchain/WHDF/ 
#make extsdk 

mkdir $path/build
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
mkdir -p $path/output/conf/RW/config/
mkdir -p $path/output/conf/OR/config/

cp $path/build/IDPS $path/output/bin/
cp $path/script/IDPS_start.sh $path/output/bin/IDPS_start.sh
cp $path/script/IDPS_stop.sh $path/output/bin/
cp $path/lib/libwebsockets.so.19 $path/output/lib/
cp $path/config/base_config.json $path/output/conf/OR/config/
cp $path/config/policy_config.json $path/output/conf/RW/config/
cp $path/config/device_info.conf $path/output/conf/OR/config/
