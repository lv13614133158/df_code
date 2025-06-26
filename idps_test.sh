
file_path="./hping3.log"
log_path="./idps_test.log"
num=0
FileMonitor="10100"
ProcessMonitor="10300"
ShellLoginMonitor="10500"
ResourceMonitor="1060001"
ResourceMonitor_cpu="1060002"
ResourceMonitor_ram="1060003"
ResourceMonitor_rom="1060004"
Network="10900"

loop() {
    type=$1
    name=$2 
        while true; 
        do
            content=$(cat "$file_path")
            matched=$(echo "$content" | grep  $type |grep $name )
            if  [ -n "$matched" ]; then
                matched=$(echo "$matched" | tail -n 1 )
                echo ""
                echo "">>$log_path
                echo "$name $type"
                echo "$name $type">>$log_path
                echo ""
                echo "">>$log_path
                echo "$matched"
                echo "$matched">>$log_path
                echo ""
                echo "">>$log_path
                break
            fi
        done
}

test() { 

clear 
echo "start test">>$log_path
echo "">>$log_path
echo "">>$log_path
loop "data" "register_key"                      #注册密钥
loop "data" "session_key"                       #协商秘钥  

loop $FileMonitor "path"                       #文件监控
loop $ProcessMonitor "body"                 # 进程监控
loop $ShellLoginMonitor "user_name"           #定时上报
loop $ResourceMonitor "cpu_usage"             #用户监控
loop $ResourceMonitor_cpu "cpu_usage"            #CPU使用率
loop $ResourceMonitor_ram "ram_rate"           #ARM使用率
loop $ResourceMonitor_rom "rom_rate"           #AOM使用率
loop $Network "TCP_SYN_SCAN"               #网络攻击
loop $Network "TCP_NULL_SCAN"          
loop $Network "TCP_FIN_SCAN"            
loop $Network "TCP_ACK_SCAN"            
loop $Network "TCP_FIN_RST_DOS"         
loop $Network "TCP_ACK_FIN_DOS"         
loop $Network "TCP_SYN_ACK_FLOOD"       
loop $Network "TCP_ACK_RST_DOS"         
loop $Network "TCP_ACK_PSH_FLOOD"       
loop $Network "TCP_SYN_FLOOD"          
loop $Network "TCP_XMAS_SCAN"          
loop $Network "UDP_SRC_PORT_ZERO"      
loop $Network "FRAGGLE_ATTACK"          
loop $Network "UDP_PORT_FLOOD"          
loop $Network "TCP_LAND_ATTACK"         
loop $Network "ICMP_LARGE_PING"         
loop $Network "TCP_SRC_PORT_ZERO"       
loop $Network "TCP_FIN_SYN_DOS"         
loop $Network "UDP_PORT_SCAN"           

echo "">>$log_path
echo "">>$log_path
echo "end test">>$log_path
echo "">>$log_path
echo "">>$log_path
}




if [ $# = 0 ]; then
    echo './idps_test.sh  ./log.log' 
else
    file_path=$1
    test
fi

