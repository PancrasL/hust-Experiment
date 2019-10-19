#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#define SIZE 1024
void printdir(char *dir, char *dest, int depth); //获取目录下的文件信息
int copy_file(const char *src, const char *dest);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("参数错误\n");
        return -1;
    }
    if (access(argv[1], F_OK) == -1)
    {
        printf("源文件不存在\n");
        return -2;
    }
    if (access(argv[1], R_OK) == -1)
    {
        printf("源文件不可读\n");
        return -3;
    }
    struct stat s_buf;
 
	stat(argv[1],&s_buf);
    if (S_ISDIR(s_buf.st_mode))//是目录，递归拷贝文件
    {
        if (access(argv[2], F_OK) == -1)
        {
            printf("目标目录不存在\n");
            return -4;
        }
        if (access(argv[2], W_OK) == -1)
        {
            printf("目标目录不可写\n");
            return -5;
        }
        char dest_dir[256];
        char src_dir[256];
        realpath(argv[2], dest_dir);
        realpath(argv[1],src_dir);
        if(strstr(dest_dir,src_dir)!=NULL)
        {
            printf("目标目录不能在源目录之下\n");
            return -6;
        }
        printdir((char *)argv[1], dest_dir, 0);//是文件夹，递归拷贝
    }
    else copy_file(argv[1],argv[2]);//是文件，直接拷贝
    return 0;
}

void printdir(char *dir, char *dest_dir, int depth)
{
    DIR *dp;
    struct dirent *entry; //目录项结构
    struct stat statbuf;  //文件状态信息
    if ((dp = opendir(dir)) == NULL)
    {
        printf("目录%s打开失败\n", dir);
        return;
    }
    chdir(dir); //设置dir为当前目录

    for (entry = readdir(dp); entry; entry = readdir(dp)) //依次读取所有的目录项
    {
        lstat(entry->d_name, &statbuf); //获取该目录项的文件信息
        //printf("%d %s\n",entry->d_type,entry->d_name);
        if (entry->d_type == 4) //是目录
        {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) //跳过.和..
                continue;
            char filename[256];
            strcpy(filename, dest_dir);
            strcat(filename, "/");
            strcat(filename, entry->d_name);
            int status;
            status = mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //创建目录
            if (status == -1)
            {
                printf("!目录%s创建失败\n", filename);
                continue;
            }
            printf("目录%s创建成功\n", filename);
            printdir(entry->d_name, filename, depth + 4); //递归输出子目录下的文件信息
        }
        else
        {
            char filename[256];
            strcpy(filename, dest_dir);
            strcat(filename, "/");
            strcat(filename, entry->d_name);

            if (copy_file(entry->d_name, filename) > 0)
            {
                printf("文件%s创建成功\n", filename);
            }
            else
                printf("!文件%s创建失败\n", filename);
        }
    }
    chdir("..");  //回到上一级目录
    closedir(dp); //关闭目录流
}
int copy_file(const char *src_file, const char *dest_file)
{
    int src, dest;
    src = open(src_file, O_RDONLY);
    if (src < 0) //打开文件失败
    {
        printf("open src file %s error\n", src_file);
        return -1;
    }
    dest = open(dest_file, O_WRONLY | O_CREAT, 0666);
    if (dest < 0) //打开文件失败
    {
        printf("open dest file %s error\n", dest_file);
        close(src); //关闭已打开的文件
        return -1;
    }
    char BUF[SIZE]; //缓冲区
    int cnt = 1;
    while (cnt)
    {
        cnt = read(src, BUF, SIZE);
        if (cnt < 0) //读取文件失败
        {
            close(src);
            close(dest); //关闭已打开的文件
            printf("reading file error\n");
            return -1;
        }
        int state = write(dest, BUF, cnt);
        if (state < 0) //写入文件失败
        {
            close(src);
            close(dest); //关闭已打开的文件
            printf("writing file error\n");
            return -1;
        }
    }
    //关闭文件
    close(src);
    close(dest);
    return 1;
}
