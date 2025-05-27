SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)

SET(TOOLCHAIN_DIR "/home/nvidia/df/HAD/S73a2/toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-aarch64-none-linux-gnu")
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-none-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-none-linux-gnu-g++)


SET(APP2_USR_DIR /home/nvidia/df/HAD/S73a2/app2/usr)
SET(APP_USR_DIR /home/nvidia/df/HAD/S73a2/app/usr)
include_directories(${APP_USR_DIR}/include)
include_directories(${APP2_USR_DIR}/include)
include_directories(${APP2_USR_DIR}/include/aarch64-linux-gnu)
include_directories(${APP_USR_DIR}/include/aarch64-linux-gnu)
link_directories(
			#/home/nvidia/df/HAD/S73a2/app/usr/hobot/lib/aarch64-linux-gnu
			#/home/nvidia/df/HAD/S73a2/app/usr/lib/aarch64-linux-gnu	
			/home/nvidia/df/HAD/S73a2/toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/libc/lib64
)