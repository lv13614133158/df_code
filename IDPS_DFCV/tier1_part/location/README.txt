1、修改inc目录下info_sec.txt-> info_sec.h，包含到要用接口的程序
2、编译程序时链接lib目录下的所有库，避免找不到符号编译问题
3、使用ids_getTboxParam接口前，必须先调用sec_api_init初始化函数并返回1，否则无法通过ids_getTboxParam获取到tbox参数。
4、双向认证初始化通过sec_api_init初始化函数完成，调用该接口即可。