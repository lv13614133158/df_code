
file_path="./hping3.log"
log_path="./idps_test.log"
loop() {
 type=$1
    echo 'Find '$type
    echo 'Find '$type>>$log_path
    while true; 
    do
        content=$(cat "$file_path")
        if  echo "$content" |grep "type"| grep -q $type; then
        matched=$(echo "$content" |grep "type"| grep $type| tail -n 1 )
        echo "**********"
        echo "**********">>$log_path
        echo "$matched"
        echo "$matched">>$log_path
        echo "**********"
        echo "**********">>$log_path
        break
        fi
    done
}

test() { 

clear 
loop "TCP_SYN_SCAN"
loop "TCP_NULL_SCAN"
loop "TCP_FIN_SCAN"
loop "TCP_ACK_SCAN"
loop "TCP_FIN_RST_DOS"
loop "TCP_ACK_FIN_DOS"
loop "TCP_SYN_ACK_FLOOD"
loop "TCP_ACK_RST_DOS"
loop "TCP_ACK_PSH_FLOOD"
loop "TCP_SYN_FLOOD"
loop "TCP_XMAS_SCAN"
loop "UDP_SRC_PORT_ZERO"
loop "FRAGGLE_ATTACK"
loop "UDP_PORT_FLOOD"
loop "TCP_LAND_ATTACK"
loop "ICMP_LARGE_PING"
loop "TCP_SRC_PORT_ZERO"
loop "TCP_FIN_SYN_DOS"
loop "UDP_PORT_SCAN"

}




if [ $# = 0 ]; then
    echo './idps_test.sh  ./log.log' 
else
    file_path=$1
    test
fi

