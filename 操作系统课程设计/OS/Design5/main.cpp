#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "blockManage_layer.h"
#include "fileControl_layer.h"
#include "fileOperation_layer.h"
#include "fileCommond.h"
using namespace std;
string path;
string username;
int isRoot;         //是root用户
extern int curDir;
extern int dirOwner; //当前目录的权限
extern SUPERBLOCK sup;
extern BITBLOCK bitB;
void get_commond(); //获取命令
void show_user();   //输出用户名

int main(void)
{
    isRoot = 0;
    dirOwner = 1;
    username = USER;
    curDir = ROOT_BLOCK_NUM;
    block_read(0, &sup);
    block_read(1, &bitB);
    while (true)
    {
        get_commond();
    }
    return 0;
}

void get_commond()
{
    string s;
    path = "/";
    while (true)
    {
        show_user();
        cin >> s;
        if (s == "ls")
        {
            my_ls();
        }
        else if (s == "cd")
        {
            my_cd();
        }
        else if (s == "mkdir")
        {
            my_mkdir();
        }
        else if (s == "mkfile")
        {
            my_mkfile();
        }
        else if (s == "rm")
        {
            my_rm();
        }
        else if (s == "reformat")
        {
            my_reformat();
        }
        else if (s == "bitmap")
        {
            display_free_1();
            display_free_2();
        }
        else if (s == "sup")
        {
            my_sup();
        }
        else if (s == "chmod")
        {
            my_chmod();
        }
        else if (s == "cat")
        {
            my_cat();
        }
        else if (s == "write")
        {
            my_write();
        }
        else if (s == "sudo")
        {
            my_sudo();
        }
        else if (s == "logout")
        {
            my_logout();
        }
        else if (s == "help")
        {
            my_help();
        }
        else
            cout << "无效命令" << endl;
    }
}
void show_user()
{
    cout << username << "@" << username << "-TM1703:" << path << "$ ";
}
