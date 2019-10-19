#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
void printdir(char *dir, int depth); //获取目录下的文件信息

void print_file_info(struct dirent *entry, struct stat statbuf, int depth); //输出文件信息
void print_file_type(struct stat statbuf);                                  //输出文件类型信息
void print_file_power(struct stat statbuf);                                 //输出文件权限信息
void print_file_owner(struct stat statbuf);                                 //输出文件拥有者
void print_file_mtime(struct stat statbuf);                                 //输出文件最后一次修改的时间
void copy_file(const char *src,const char *dest);
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("参数错误\n");
        return -1;
    }
    printdir((char *)argv[1], 0);
    return 0;
}

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry; //目录项结构
    struct stat statbuf;  //文件状态信息
    if ((dp = opendir(dir)) == NULL)
    {
        printf("目录打开失败\n");
        return;
    }
    chdir(dir); //设置dir为当前目录

    for (entry = readdir(dp); entry; entry = readdir(dp)) //依次读取所有的目录项
    {
        lstat(entry->d_name, &statbuf); //获取该目录项的文件信息
        if (entry->d_type == 4)         //是目录
        {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) //跳过.和..
                continue;
            print_file_info(entry, statbuf, depth); //输出目录文件信息
            printdir(entry->d_name, depth + 4);     //递归输出子目录下的文件信息
        }
        else
        {
            print_file_info(entry, statbuf, depth); //输出非目录文件信息
        }
    }
    chdir("..");//回到上一级目录
    closedir(dp);//关闭目录流
}
void print_file_info(struct dirent *entry, struct stat statbuf, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        putchar(' ');
    }                                  //缩进
    print_file_type(statbuf);          //输出文件类型
    print_file_power(statbuf);         //输出文件权限
    printf("%-3d", depth);             //输出文件深度
    print_file_owner(statbuf);         //输出文件用户
    printf("%-10lu", statbuf.st_size); //输出文件大小
    print_file_mtime(statbuf);         //输出文件最后一次修改的时间
    printf("%-20s\n", entry->d_name);  //输出文件名
}
void print_file_type(struct stat statbuf)
{
    if (S_ISREG(statbuf.st_mode))
        putchar('-'); //普通文件
    else if (S_ISDIR(statbuf.st_mode))
        putchar('d'); //目录文件
    else if (S_ISCHR(statbuf.st_mode))
        putchar('c'); //字符设备文件
    else if (S_ISBLK(statbuf.st_mode))
        putchar('b'); //块特殊文件
    else if (S_ISFIFO(statbuf.st_mode))
        putchar('p'); //管道文件
    else if (S_ISLNK(statbuf.st_mode))
        putchar('l'); //链接文件
    else if (S_ISSOCK(statbuf.st_mode))
        putchar('s'); //socket文件
    else
        putchar('?'); //未知文件
}
void print_file_power(struct stat statbuf)
{
    unsigned short st_mode = statbuf.st_mode;
    // 判断USR权限
    printf("%c", st_mode & S_IRUSR ? 'r' : '-');
    printf("%c", st_mode & S_IWUSR ? 'w' : '-');
    printf("%c", st_mode & S_IXUSR ? 'x' : '-');

    // 判断GRP权限
    printf("%c", st_mode & S_IRGRP ? 'r' : '-');
    printf("%c", st_mode & S_IWGRP ? 'w' : '-');
    printf("%c", st_mode & S_IXGRP ? 'x' : '-');

    // 判断OTH权限
    printf("%c", st_mode & S_IROTH ? 'r' : '-');
    printf("%c", st_mode & S_IWOTH ? 'w' : '-');
    printf("%c ", st_mode & S_IXOTH ? 'x' : '-');
}
void print_file_owner(struct stat statbuf)
{
    char *msg="???";
    struct passwd *temp;
    temp=getpwuid(statbuf.st_uid);
    temp?printf("%-10s", temp->pw_name):printf("%-10s",msg);
    temp=getpwuid(statbuf.st_gid);
    temp?printf("%-10s", temp->pw_name):printf("%-10s",msg);
}
void print_file_mtime(struct stat statbuf)
{
    time_t mtime = statbuf.st_mtime;
    char *p;
    p = ctime(&mtime);
    p[strlen(p) - 1] = 0;
    printf("%-30s", p);
}