#!/bin/bash


# ====================
# IDPS 测试主逻辑
# ====================
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_log_file>"
    exit 1
fi

file_path="$1"
output_file="idps_test.log"


# 清空输出文件
echo -n "" > "$output_file"

FileMonitor="10100"
ProcessMonitor="10300"
ShellLoginMonitor="10500"
ResourceMonitor="1060001"
ResourceMonitor_cpu="1060002"
ResourceMonitor_ram="1060003"
ResourceMonitor_rom="1060004"
Network="10900"

test_event() {
    type=$1
    name=$2
    echo "正在测试 $name $type"
while true; do
    content=$(cat "$file_path")
    matched=$(echo "$content" | grep "$type" | grep -i "$name")
    if [ -n "$matched" ]; then
        matched=$(echo "$matched" | tail -n 1)
        echo "">> "$output_file"
        echo "$name $type">> "$output_file"
        echo "">> "$output_file"
        echo "$matched" >> "$output_file"
        echo "测试完成 已保存"
        break
    fi
done
    
}

# 测试事件列表
test_event "data" "register_key"
test_event "data" "session_key"
test_event "$FileMonitor" "1.txt"
test_event "$ProcessMonitor" "11"
test_event "$ShellLoginMonitor" "user_name"
test_event "$ResourceMonitor" "cpu_usage"
test_event "$ResourceMonitor_cpu" "cpu_usage"
test_event "$ResourceMonitor_ram" "ram_rate"
test_event "$ResourceMonitor_rom" "rom_rate"
test_event "$Network" "TCP_SYN_SCAN"
test_event "$Network" "TCP_NULL_SCAN"
test_event "$Network" "TCP_FIN_SCAN"
test_event "$Network" "TCP_ACK_SCAN"
test_event "$Network" "TCP_FIN_RST_DOS"
test_event "$Network" "TCP_ACK_FIN_DOS"
test_event "$Network" "TCP_SYN_ACK_FLOOD"
test_event "$Network" "TCP_ACK_RST_DOS"
test_event "$Network" "TCP_ACK_PSH_FLOOD"
test_event "$Network" "TCP_SYN_FLOOD"
test_event "$Network" "TCP_XMAS_SCAN"
test_event "$Network" "UDP_SRC_PORT_ZERO"
test_event "$Network" "FRAGGLE_ATTACK"
test_event "$Network" "UDP_PORT_FLOOD"
test_event "$Network" "TCP_LAND_ATTACK"
test_event "$Network" "ICMP_LARGE_PING"
test_event "$Network" "TCP_SRC_PORT_ZERO"
test_event "$Network" "TCP_FIN_SYN_DOS"
test_event "$Network" "UDP_PORT_SCAN"

# 格式化临时文件中的内容

echo "测试完成  保存文件： $output_file"