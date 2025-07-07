#!/bin/bash    
# IDPS start up script 
#添加本地执行路径
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/

APP_TO_START="IDPS"
APP_PATH="/usrdata/appset/bin/"

echo "killall $APP_TO_START"
killall $APP_TO_START

while true; 
do
	PROCESS_NUM=`pidof IDPS`
	if [ "$PROCESS_NUM" == "" ];then
		cd $APP_PATH
		./$APP_TO_START > /dev/null 2>&1 &
		echo "$APP_TO_START START"
	fi
	#echo "IDPS AREADY RUNNING" ${PROCESS_NUM}
	sleep 10
done
