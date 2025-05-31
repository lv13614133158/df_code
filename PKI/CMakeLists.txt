# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
set(TOOLCHAIN_DIR "/home/nvidia/df/HAD/S73a2/toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-aarch64-none-linux-gnu")
set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-none-linux-gnu-g++)


project(pki_test C CXX)
cmake_minimum_required(VERSION 3.4.1)


set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)


set(CURRENT_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
#生成gdb的调试信息和不进行代码优化
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")

# 设置编译时缓冲区溢出检查
add_definitions(-D_FORTIFY_SOURCE=2)
#add_compile_definitions(-D_FORTIFY_SOURCE=2)

# 设置堆栈不可执行、重定位只读和立即绑定
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now")

# 设置 空间随机化 堆栈保护
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wno-error=unused-function -Wno-error=pointer-sign")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wno-error=unused-function -Wno-error=pointer-sign -fPIE -fstack-protector-all -fsigned-char")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wno-error=unused-function -Wno-error=pointer-sign -Wno-return-local-addr -fPIE -fstack-protector-all -fsigned-char")
#无视错误警告
# 忽略 sqlite3.c 的局部变量返回警告
set(SQLITE_SRC "${CMAKE_SOURCE_DIR}/function/common/src/sqlite/sqlite3.c")
set_source_files_properties(${SQLITE_SRC} PROPERTIES COMPILE_FLAGS "-Wno-return-local-addr")
# 禁用 data_dispatcher.c 的 -Wstringop-overflow 警告
set(DATA_DISPATCHER_SRC "${CMAKE_SOURCE_DIR}/function/networkmonitor/src/networkapi/data_dispatcher.c")
set_source_files_properties(${DATA_DISPATCHER_SRC} PROPERTIES COMPILE_FLAGS "-Wno-stringop-overflow")
# 设置 strip 
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_BUILD_TYPE "RELEASE")


#头文件路径




#交叉编译标准库

set(SDK_USR_DIR /home/nvidia/df/HAD/S73a2/sdk/usr)

include_directories(${SDK_USR_DIR}/hobot/include/aarch64-linux-gnu) #1.1.1
include_directories(${SDK_USR_DIR}/hobot/include) #1.1.1
include_directories(${SDK_USR_DIR}/include/aarch64-linux-gnu) #curl.h
include_directories(${SDK_USR_DIR})


set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(link_USR_DIR /home/nvidia/df/HAD/S73a2/sdk/usr)
# link_directories(${link_USR_DIR}/lib/aarch64-linux-gnu)
#  link_directories(${link_USR_DIR}/hobot/lib)
link_directories(/home/nvidia/df/PKI/PKI)



add_executable(pki_test 
		${CMAKE_SOURCE_DIR}/test_main.c

		)

#预编译好的库
target_link_libraries( # Specifies the target library.
	pki_test
	${CMAKE_SOURCE_DIR}/libcurl.a

	-lteec
	-lsecure_storage
	-lalog
	-lssl
	-lcrypto
	${CMAKE_SOURCE_DIR}/libssphad.so
	-lpthread
    -ldl
    -lrt
    -lstdc++
	)

