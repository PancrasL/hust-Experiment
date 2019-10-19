#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 1024
int main(void)
{
    int fd;
    char buf[MAX_SIZE] = "Original"; //从设备中读取的信息
    char writes[MAX_SIZE];           //要写入设备的信息
    char dir[50] = "/dev/lpzdev";   //设备所在路径
    int i = 0;
    fd = open(dir, O_RDWR | O_NONBLOCK);
    if (fd != -1)
    {
        read(fd, buf, sizeof(buf));
        printf("设备初始信息：%s\n", buf);
        printf("输入信息 :");
        fgets(writes,MAX_SIZE,stdin);
        write(fd, writes, sizeof(writes));
        read(fd, buf, sizeof(buf));
        printf("设备输出信息: %s\n", buf);
        close(fd);
        return 0;
    }
    else
    {
        printf("设备打开失败\n");
        return -1;
    }
}