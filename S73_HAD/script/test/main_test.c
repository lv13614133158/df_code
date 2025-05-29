
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

volatile int run_cpu_load = 1;
#define MAX_CORES 64

void* cpu_intensive_task(void* arg) {
    unsigned long long count = 0;
    while (run_cpu_load) {
        count++;
        if ((count % 100000000) == 0) {
            // 每计数一定次数后打印一次
            // printf("Thread %lu counting...\n", pthread_self());
        }
    }
    return NULL;
}

int get_cpu_cores() {
    FILE* fp = fopen("/proc/cpuinfo", "r");
    if (!fp) {
        perror("fopen /proc/cpuinfo failed");
        return -1;
    }

    char line[128];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "processor", 9) == 0)
        {
            count++;
        }
            
    }
    fclose(fp);
    return count;
}
// 启动指定数量的线程进行 CPU 占用
void start_cpu_load(int num_threads) {
    pthread_t threads[MAX_CORES];
    run_cpu_load = 1;
    int num;
    for (int i = 0; i < num_threads; ++i) {
        if (pthread_create(&threads[i], NULL, cpu_intensive_task, NULL) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("已启动 %d 个线程模拟 CPU 占用，请按任意键停止。\n", num_threads);
   
    getchar();
    run_cpu_load = 0;
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
     printf("CPU 占用已清除。\n");
     sleep(2);
}

void  file_test()
{
    FILE *fp;
    int num = 0, c;
    char path[256];

    printf("请输入要创建文件的位置和名称  （例如 ./testfile.txt）   回车结束\n");
    scanf("%s", path);
    while ((c = getchar()) != '\n' && c != EOF); 
    fp = fopen(path, "wb");
    if (!fp) {
        printf("无法打开文件 %s\n", path);
        sleep(2);
        return;
    }
    printf("创建成功   文件路径%s\n",path);
    printf("等待删除 请输入任意键\n");
    getchar();
    remove(path);
    printf("删除成功  \n");
    sleep(2);

    return;
}


void cpu_test()
{
    system("clear");
    int cpu_cores = get_cpu_cores();
    if (cpu_cores <= 0) {
        fprintf(stderr, "无法获取 CPU 核心数\n");

        return ;
    }else 
    {
        printf("CPU 核心数 = %d\n",cpu_cores);
    }
   //休眠等待

        printf("请输入要占用的 CPU 核心数 (0 表示返回): ");
        int num,c;
        scanf("%d", &num);
        while ((c = getchar()) != '\n' && c != EOF); 

    if (num == 0) {
        printf("正在清理之前的负载任务...\n");
        // 在 Linux 中无法直接杀死其他进程中由自己创建的线程，所以通过关闭标志即可
        run_cpu_load = 0;
        sleep(1);  // 给线程一点时间退出
        printf("CPU 占用已清除。\n");
        return ;
    } else if (num > 0 && num <= cpu_cores) {
        start_cpu_load(num);
    } else {
        printf("无效的输入，数值应在 0 到 %d 之间。\n", cpu_cores);
    } 
}

void arm_test()
{
    char * malloc_ptr;
    printf("请输入要测试的RAM大小 num   单位MB   范围 1~5120\n");
    int num,c;
  
    scanf("%d", &num);
    while ((c = getchar()) != '\n' && c != EOF); 
    if (num!=0&&num<=5120)
    {
        malloc_ptr=(char *)malloc(num*1024*1024);
        memset(malloc_ptr, 0, num * 1024 * 1024); 
        printf("等待释放内存，请按任意键停止\n");
        
        getchar(); 
        if(malloc_ptr!=NULL)
        {
            free(malloc_ptr);
            printf("释放内存成功\n");
        }
    }
    sleep(2);
}
void aom_test()
{ 
    FILE *fp;
    int num = 0, c;
    char path[256];

    printf("请输入要测试的ROM文件位置  （例如 ./testfile.txt）   回车结束\n");
    scanf("%s", path);
    while ((c = getchar()) != '\n' && c != EOF); 
    fp = fopen(path, "wb");
    if (!fp) {
        printf("无法打开文件 %s\n", path);
        sleep(2);
        return;
    }

    printf("请输入要测试的ROM大小 num   单位MB   范围 1~2048\n");
    scanf("%d", &num);
    while ((c = getchar()) != '\n' && c != EOF); 
    if (num>=2048)
    {
       printf("num %d  错误 范围1-2048\n", num);
       sleep(2);
       return;
    }
    

    printf("开始 ROM 测试...\n");

    char *buffer = (char *)malloc(1024 * 1024); // 1MB buffer
    if (!buffer) {
        fprintf(stderr, "内存分配失败\n");
        fclose(fp);
        return;
    }
    
    memset(buffer, 'A', 1024 * 1024);
    long long size_bytes = (long long)num * 1024 * 1024;
    printf("尝试向 %s 写入数据\n", path);
    long long written = 0;
    while (written < size_bytes) {
        size_t to_write = (size_bytes - written) > (1024 * 1024) ? (1024 * 1024) : (size_t)(size_bytes - written);
        fwrite(buffer, 1, to_write, fp);
        written += to_write;
    }

    free(buffer);
    fclose(fp);

    printf("已成功写入 %d MB 到 %s\n", num, path);
    printf("等待删除  %s 文件...\n",path);
    getchar();
    remove(path);
    printf("删除成功\n");
    sleep(2);
}
void  resource_test()
{
   for(;;)
    {
        system("clear");
        printf("*********************************\n");
        printf("*********************************\n");
        printf("请输入要测试的功能 1 表示CPU占用测试\n");
        printf("请输入要测试的功能 2 表示RAM占用测试\n");
        printf("请输入要测试的功能 3 表示ROM占用测试\n");
        printf("请输入要测试的功能 0 表示返回上一页\n");
        printf("*********************************\n");
        printf("*********************************\n");
        int num,c;

        scanf("%d", &num);
        while ((c = getchar()) != '\n' && c != EOF); 
         if(num == 0)
        {
            return;
        }
        else if(num == 1)
        {
            printf("CPU测试\n");
            cpu_test();
        }
        else if(num == 2)
        {
            printf("RAM测试\n");
            arm_test();
            
        }else if(num == 3)
        {
            printf("ROM测试\n");
            aom_test();
        }
        else
        {
            printf("无效的输入，请重新输入。\n");
            sleep(1);
        }
    }
}
int main()
{

    for(;;)
    {
        int num,c;
        system("clear");
        printf("******************************\n");
        printf("******************************\n");
        printf("请输入要测试的功能 1 表示文件测试\n");
        printf("请输入要测试的功能 2 表示资源测试\n");
        printf("******************************\n");
        printf("******************************\n");
      
        scanf("%d", &num);
        while ((c = getchar()) != '\n' && c != EOF); 
        if(num == 1)
        {
            printf("文件测试\n");
            file_test();
        }
        else if(num == 2)
        {
            printf("资源测试\n");
            resource_test();
        }
        else
        {
            printf("无效的输入，请重新输入。\n");
            sleep(1);
        }

    }
    
}