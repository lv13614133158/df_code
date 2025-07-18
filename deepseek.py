#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import warnings



# 设置中文字体和解决负号问题
plt.rcParams["font.sans-serif"] = ["Noto Sans CJK JP"]  # 使用支持中文的字体
plt.rcParams["axes.unicode_minus"] = False  # 解决负号 '-' 显示为方块的问题

# 读取CSV文件（跳过格式错误的行）
try:
    df = pd.read_csv("monitor_info.csv", skiprows=1, header=None, names=[
        "time", "usr_cpu", "sys_cpu", "idle_cpu", "used_mem", "free_mem", 
        "buff_mem", "idps_cpu", "idps_mem"
    ])
except pd.errors.ParserError:
    print("发现格式错误的行，正在尝试跳过...")
    df = pd.read_csv("monitor_info.csv", skiprows=1, header=None, names=[
        "time", "usr_cpu", "sys_cpu", "idle_cpu", "used_mem", "free_mem", 
        "buff_mem", "idps_cpu", "idps_mem"
    ], on_bad_lines='skip')

# 清理数据：移除无效值（如 "id"）并转换为数值
df["idle_cpu"] = pd.to_numeric(df["idle_cpu"], errors="coerce")
df = df.dropna(subset=["idle_cpu"])

# 计算CPU使用率的平均值
avg_usr = df["usr_cpu"].mean()
avg_sys = df["sys_cpu"].mean()
avg_idle = df["idle_cpu"].mean()

# 清理数据：移除无效值并转换为数值
df["idps_cpu"] = pd.to_numeric(df["idps_cpu"], errors="coerce")
df["idps_mem"] = pd.to_numeric(df["idps_mem"], errors="coerce")
df = df.dropna(subset=["idps_cpu", "idps_mem"])

# 计算 IDPS 程序的 CPU 和内存使用率平均值
avg_idps_cpu = df["idps_cpu"].mean() if "idps_cpu" in df.columns else 0.0
avg_idps_mem = df["idps_mem"].mean() if "idps_mem" in df.columns else 0.0

avg_cpu = avg_usr + avg_sys  # 总CPU使用率
avg_arm = 0  # 假设ARM默认值为0，如有实际列请替换
avg_aom = 0  # 假设AOM默认值为0，如有实际列请替换

# 计算内存平均值
avg_used_mem = df["used_mem"].mean()
avg_free_mem = df["free_mem"].mean()
avg_buff_mem = df["buff_mem"].mean()

# 打印详细数据信息
total_cpu = avg_usr + avg_sys + avg_idle


# 添加 IDPS 程序信息到标签
if avg_idps_cpu > 0:
    idps_cpu_label = f'\\n(IDPS: {avg_idps_cpu:.1f}% )'
else:
    idps_cpu_label = ""

if avg_idps_mem > 0:
    idps_mem_label = f'\\n(IDPS: {avg_idps_mem:.0f} KB)'
else:
    idps_mem_label = ""

# 定义设备整体使用分布数据
labels_device = ["CPU 使用率", "ARM 使用率", "AOM 使用率"]
sizes_device = [avg_cpu, avg_arm, avg_aom]
colors_device = ["#ff9999", "#66b3ff", "#99ff99"]

# 定义 CPU 使用分布数据
labels_cpu = ['IDPS CPU', '其他 CPU', 'CPU 空闲率']
sizes_cpu = [
    avg_idps_cpu if avg_idps_cpu > 0 else 0.1,
    (avg_usr + avg_sys) - avg_idps_cpu if (avg_usr + avg_sys) > avg_idps_cpu and avg_idps_cpu > 0 else 0.1,
    avg_idle
]
colors_cpu = ['#ff9999', '#ffcc99', '#66b3ff']

# 定义 内存 使用分布数据
labels_mem = ['IDPS 内存', '其他内存', '剩余内存']
sizes_mem = [
    avg_idps_mem if avg_idps_mem > 0 else 0.1,
    avg_used_mem - avg_idps_mem if avg_used_mem > avg_idps_mem and avg_idps_mem > 0 else 0.1,
    avg_free_mem
]
colors_mem = ['#99ff99', '#cce5ff', '#ffcc99']

# 创建一个窗口，包含两个扇形图
fig, axs = plt.subplots(1, 2, figsize=(14, 6))

# 图 1：CPU 使用率与空闲率（带 IDPS 占比）
axs[0].pie(
    sizes_cpu,
    autopct="%1.1f%%",
    startangle=90,
    colors=colors_cpu,
    pctdistance=0.75,
    wedgeprops={"edgecolor": "white", "linewidth": 1},
    labels=None  # 隐藏标签
)
axs[0].legend(labels_cpu, loc="upper right", title="CPU 使用分布")
axs[0].set_title("CPU 使用率与 IDPS 占比", fontsize=14)

# 图 2：内存使用率与空闲率（带 IDPS 占比）
axs[1].pie(
    sizes_mem,
    autopct="%1.1f%%",
    startangle=90,
    colors=colors_mem,
    pctdistance=0.75,
    wedgeprops={"edgecolor": "white", "linewidth": 1},
    labels=None  # 隐藏标签
)
axs[1].legend(labels_mem, loc="upper right", title="内存使用分布")
axs[1].set_title("内存使用率与 IDPS 占比", fontsize=14)

# 设置整体布局并显示
plt.tight_layout()

# 添加系统资源详情文本到窗口左下角
resource_info_kb = (
    "CPU 使用详情:\n"
    f"用户态 CPU 使用率: {avg_usr:.1f}%\n"
    f"内核态 CPU 使用率: {avg_sys:.1f}%\n"
    f"CPU 空闲率: {avg_idle:.1f}%\n"
    f"总 CPU 使用率: {avg_usr + avg_sys:.1f}%\n\n"
    "内存使用详情:\n"
    f"已使用内存: {avg_used_mem:.0f} KB\n"
    f"剩余内存: {avg_free_mem:.0f} KB\n"
    f"缓冲区内存: {avg_buff_mem:.0f} KB\n\n"
    "IDPS 程序资源占用:\n"
    f"IDPS CPU 占用率: {avg_idps_cpu:.1f}%\n"
    f"IDPS 内存占用: {avg_idps_mem:.0f} KB\n"
)
resource_info_mb = (
    "CPU 使用详情:\n"
    f"用户态 CPU 使用率: {avg_usr:.1f}%\n"
    f"内核态 CPU 使用率: {avg_sys:.1f}%\n"
    f"CPU 空闲率: {avg_idle:.1f}%\n"
    f"总 CPU 使用率: {avg_usr + avg_sys:.1f}%\n\n"
    "内存使用详情:\n"
    f"已使用内存: {avg_used_mem:.0f} MB\n"
    f"剩余内存: {avg_free_mem:.0f} MB\n"
    f"缓冲区内存: {avg_buff_mem:.0f} MB\n\n"
    "IDPS 程序资源占用:\n"
    f"IDPS CPU 占用率: {avg_idps_cpu:.1f}%\n"
    f"IDPS 内存占用: {avg_idps_mem:.0f} MB\n"
)
fig.text(0.01, 0.01, resource_info_mb, fontsize=9, ha='left', va='bottom',
         bbox=dict(boxstyle='round,pad=0.5', facecolor='white', edgecolor='gray', alpha=0.9))

plt.show()