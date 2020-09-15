#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EVENTS 1024   //监听上限
#define BUFLEN 4095       //缓冲区大小
#define SERV_PORT         //监听端口号

void recvdata(int fd,int events,void* arg);
void senddata(int fd,int events,void* arg);

struct myevent_s
{
    int fd;               //要监听的文件描述符
    int events;           //对应的监听事件，EPOLLIN 和 EPLLOUT
    void* arg;            //指向自己结构图指针
    void (*call_back)(int fd,int events,void* arg);
                          //回调函数
    int status;           //是否在监听: 1->在红黑树上(监听)，0->不在(不监听)
    char buf[BUFLEN];
    int len; 
    long last_active;     //记录每次加入红黑树 g_efd 的时间值
};

int g_efd;                //全局变量
struct myevent_s g_evevts[MAX_EVENTS+1];
                          //自定义结构体类型数组,+1-->listen

int main()
{
    //设置信号处理
    //进程退出信号

    //日志模块初始化

    //初始化数据库配置

    




    return 0;
}
