#include "linux/kernel.h"
#include "linux/module.h"
#include "linux/fs.h"
#include "linux/init.h"
#include "linux/types.h"
#include "linux/errno.h"
#include "linux/uaccess.h"
#include "linux/kdev_t.h"

#define MAX_SIZE 1024 //设备申请的最大内存空间

int my_open(struct inode *inode, struct file *file);                               //open
int my_release(struct inode *inode, struct file *file);                            //release
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f);        //read
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f); //write

char data[MAX_SIZE]="new Device";      //设备申请的空间
int device_num;           //设备号
char *devName = "lpzdev"; //设备名

struct file_operations pStruct = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

/*模块注册*/
int init_module()
{
    if ((device_num = register_chrdev(0, devName, &pStruct)) < 0) //申请失败
    {
        printk("设备号申请失败.\n");
        return -1;
    }
    else
    {
        printk("设备%d注册成功\n",device_num);
        return 0;
    }
}

/*模块注销*/
void cleanup_module()
{
    unregister_chrdev(device_num, devName); //注销设备
    printk("设备注销成功.\n");
}

/*打开设备*/
int my_open(struct inode *inode, struct file *file)
{
    printk("设备打开成功.\n");
    return 0;
}

/*关闭设备*/
int my_release(struct inode *inode, struct file *file)
{
    printk("设备关闭成功.\n");
    return 0;
}

/*读数据*/
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
    return copy_to_user(user, data, sizeof(data)); //成功返回0,失败返回未完成copy的字节数
}

/*写数据*/
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
    return copy_from_user(data, user, sizeof(data)); //成功返回0,失败返回未完成copy的字节数
}