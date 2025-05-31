#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <openssl/pkcs12.h>
#include <openssl/x509v3.h>
#include <openssl/asn1.h>
#include <curl/curl.h>
#include "dfssphad.h"
#include <time.h>
#include <sys/times.h>
#include <assert.h>
#include <unistd.h>

//#define DEVICE_ID               "DEVICESGW"
// #define DEVICE_ID               "DEVICETBOX"
//#define DEVICE_ID               "TEST20230921YX"
//#define DEVICE_ID               "S73OTA2024011512345"
//#define DEVICE_ID               "P123456789012345"
//#define DEVICE_ID               "P008004460020938"
#define DEVICE_ID               "dfgf202408260001"
// #define DEVICE_ID               "dfgf202408260002" 
// #define DEVICE_ID               "tboxtest202501191706" 

#define STACKSIZE               8

pthread_mutex_t lock;

static void print_option()
{
    printf("Usage: test.bin [NUM]\n");
    printf( "NUM : \n"
            "\t1      get cert statue\n"
            "\t2      get cert statue by id\n"
            "\t3      import root cert\n"
            "\t4      import general cert\n"
            "\t5      request device cert\n"
            "\t6      update device cert\n"
            "\t7      delete root cert\n"
            "\t8      delete middle cert\n"
            "\t9      delete general cert\n"
            "\t10     delete device cert\n"
            "\t11     read root cert\n"
            "\t12     read device cert\n"
            "\t13     read device key\n"
            "\t14     import device cert\n"
            );
    printf("\t------20241128 DEBUG thread-----\n");
}

static void getCertStatueTest()
{
    printf("cert state=0x%04X\n", getCertState());
}
static void getCertStatueByIdTest()
{
    printf("cert state=0x%04X\n", getCertStateByDeviceId(DEVICE_ID, strlen(DEVICE_ID)));
}

static void importRootCertTest()
{
    FILE *fp = NULL;
    char cert[4096] = {'\0'};
    size_t certLen = 4096;

    fp = fopen("test/new_root.cert", "r");
    if(fp == NULL) {
        printf("open test/new_root.cert error\n");
        printf("please save root cert into test/new_root.cert\n");
        return;
    }
    certLen = fread(cert, 1, 4096, fp);
    printf("read root cert[len=%ld]:\n%s\n", certLen, cert);
    fclose(fp);

    printf("importRootCert ret=0x%04X\n", importRootCert(cert, certLen));
}
static void importGeneralCertTest()
{
    FILE *fp = NULL;
    char password[64] = {'\0'};
    size_t passwordLen = 64;
    char cert[6000] = {'\0'};
    size_t certLen = 6000;

    fp = fopen("test/tongyongzhegnshu_miyao.key", "r");
    if(fp == NULL) {
        printf("open test/tongyongzhegnshu_miyao.key error\n");
        printf("please save universal cert PASSWORD into test/tongyongzhegnshu_miyao.key\n");
        return;
    }
    passwordLen = fread(password, 1, 64, fp);
    if(passwordLen - 1 > 0 && password[passwordLen - 1] == '\n') {
        password[passwordLen - 1] = 0;
        passwordLen -= 1;
    }
    printf("read general cert password[len=%ld]:\n%s\n", passwordLen, password);
    fclose(fp);

    fp = fopen("test/tongyongzhegnshu.cert", "rb");
    if(fp == NULL) {
        printf("open test/tongyongzhegnshu.cert error\n");
        printf("please save p12 universal cert into test/tongyongzhegnshu.cert\n");
        return;
    }
    certLen = fread(cert, 1, 6000, fp);
    fclose(fp);
    printf("certLen=%ld\n", certLen);
    printf("importGeneralCert ret=0x%04X\n", importGeneralCert(cert, password, certLen, passwordLen));
    
}
static void requestCertTest()
{
    // system("rm /oemdata/certstate/certstate");
    printf("requestCert ret=0x%04X\n", requestCert(DEVICE_ID, strlen(DEVICE_ID)));
}
static void updateCertTest()
{
    // system("rm /oemdata/certstate/certstate");
    printf("updateCert ret=0x%04X\n", updateCert());
}
static void requestCertTime()
{
    printf("申请设备证书测试\n");
    //开始测试
    int testTimes = 100;
    int i = 0;
    struct tms start_tm;
    struct tms end_tm;
    clock_t start_time = times(&start_tm);
    for(i = 0; i < testTimes; i++){
        // system("rm /oemdata/certstate/certstate");
        printf("requestCert ret=0x%04X\n", requestCert(DEVICE_ID, strlen(DEVICE_ID)));
    }
    clock_t end_time = times(&end_tm);
    printf("运行次数：%d,平均运行时间：%fms\n", testTimes, ((double)(end_time - start_time)/sysconf(_SC_CLK_TCK)) * 1000 / testTimes);
}
static void updateCertTime()
{
    printf("更新设备证书测试\n");
    //开始测试
    int testTimes = 1;
    int i = 0;
    struct tms start_tm;
    struct tms end_tm;
    clock_t start_time = times(&start_tm);
    for(i = 0; i < testTimes; i++){
        // system("rm /oemdata/certstate/certstate");
        printf("updateCert ret=0x%04X\n", updateCert());
    }
    clock_t end_time = times(&end_tm);
    printf("运行次数：%d,平均运行时间：%fms\n", testTimes, ((double)(end_time - start_time)/sysconf(_SC_CLK_TCK)) * 1000 / testTimes);
}

static void deleterootCertTest()
{
    printf("deleterootCert %s !\n", deleteCert("rootCert") == 0 ? "success" : "failed");
}

static void deleteMiddleCert()
{
    printf("deleteMiddleCert %s !\n", deleteCert("middleCert") == 0 ? "success" : "failed");
}
static void deleteGeneralCert()
{
    printf("deleteGeneralCert %s !\n", deleteCert("generalCert") == 0 ? "success" : "failed");
    printf("deleteGeneralKey %s !\n", deleteCert("generalKey") == 0 ? "success" : "failed");
}

static void deleteDeviceCert()
{
    printf("deleteDeviceCert %s !\n", deleteCert("deviceCert") == 0 ? "success" : "failed");
    printf("deleteDeviceKey %s !\n", deleteCert("deviceKey") == 0 ? "success" : "failed");
}

static void readRootCert() {
    char cert[6000] = {'\0'};
    size_t certLen = 6000;
    int res = DSec_ReadFile("rootCert", cert, certLen);
    printf("rootCert: \n%s\nlength: %d\n", cert, res);
}

static void readDeviceCert() {
    char cert[6000] = {'\0'};
    size_t certLen = 6000;
    int res = DSec_ReadFile("deviceCert", cert, certLen);
    printf("deviceCert: \n%s\nlength: %d\n", cert, res);
}

static void readDeviceKey() {
    char password[6000] = {'\0'};
    size_t passwordLen = 6000;
    int res = DSec_ReadFile("deviceKey", password, passwordLen);
    printf("deviceKey: \n%s\nlength: %d\n", password, res);
}

static void importDeviceCertTest() {
    FILE *fp = NULL;
    // cert
    char cert[4096] = {'\0'};
    size_t certLen = 4096;

    fp = fopen("test/device_cert.pem", "r");
    if(fp == NULL) {
        printf("open test/device_cert.pem error\n");
        printf("please save device cert into test/device_cert.pem\n");
        return;
    }
    certLen = fread(cert, 1, 4096, fp);
    printf("read root cert[len=%ld]:\n%s\n", certLen, cert);
    fclose(fp);

    printf("importDeviceCert ret=0x%04X\n", importDeviceCert(cert, certLen));

    // key
    char key[4096] = {'\0'};
    size_t keyLen = 4096;
    fp = fopen("test/device_key.pem", "r");
    if(fp == NULL) {
        printf("open test/device_key.pem error\n");
        printf("please save device cert into test/device_key.pem\n");
        return;
    }
    keyLen = fread(key, 1, 4096, fp);
    printf("read device key[len=%ld]:\n%s\n", keyLen, key);
    fclose(fp);

    printf("importDeviceKey ret=0x%04X\n", importDeviceKey(key, keyLen));

}


void* thread_func(void* arg)
{
    char** argv = (char**)arg;
    if(strcmp(argv[1], "1") == 0) {
        getCertStatueTest();
    } else if(strcmp(argv[1], "2") == 0) {
        getCertStatueByIdTest();
    } else if(strcmp(argv[1], "3") == 0) {
        importRootCertTest();
    } else if(strcmp(argv[1], "4") == 0) {
        importGeneralCertTest();
    } else if(strcmp(argv[1], "5") == 0) {
        requestCertTest();
    } else if(strcmp(argv[1], "6") == 0) {
        updateCertTest();
    } else if(strcmp(argv[1], "7") == 0) {
       // deleterootCertTest();
    } else if(strcmp(argv[1], "8") == 0) {
       // deleteMiddleCert();
    } else if(strcmp(argv[1], "9") == 0) {
       // deleteGeneralCert();
    } else if(strcmp(argv[1], "10") == 0) {
        //deleteDeviceCert();
    } else if(strcmp(argv[1], "11") == 0) {
        readRootCert();
    } else if(strcmp(argv[1], "12") == 0) {
        readDeviceCert();
    } else if(strcmp(argv[1], "13") == 0) {
        readDeviceKey();
    } else if(strcmp(argv[1], "14") == 0) {
        importDeviceCertTest();
    }else {
        print_option();
    }
    return NULL;
}

void my_callback(int level, const char* msg) {
    if (level <= LOG_INFO) { // 自行定义过滤条件
        FILE* fp = fopen("./pki.log", "a");
        if (fp) {
            fprintf(fp, "%s\n", msg);
            fclose(fp);
        }
    }
}


int main(int argc, char **argv) {

    // 注册回调函数
    set_log_callback(my_callback);
    if (argc < 2) {
        print_option();
        return 1;
    }
    pthread_mutex_init(&lock, NULL);

    pthread_t thread;
    pthread_attr_t attr;
    size_t stacksize;

    // 初始化线程属性并设置栈大小
    pthread_attr_init(&attr);
    stacksize = 1024 * STACKSIZE; // 设置栈大小 12kb
    pthread_attr_setstacksize(&attr, stacksize);
    printf("栈内存：%d kb\n", STACKSIZE);

    // 创建一个线程来运行主程序逻辑
    if (pthread_create(&thread, &attr, thread_func, argv)) {
        fprintf(stderr, "创建线程失败\n");
        pthread_mutex_destroy(&lock);
        pthread_attr_destroy(&attr);
        return 1;
    }
    
    // 等待线程完成
    pthread_join(thread, NULL);
    
    // printf("主线程已完成\n");
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock);

    return 0;
}
