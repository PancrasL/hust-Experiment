#include "fileCommond.h"
#include <string>
#include "fileControl_layer.h"
#include "fileOperation_layer.h"
#include "filesystem_struct.h"
extern int curDir;
extern string path;
extern string username;
extern int isRoot;
extern int dirOwner; //当前目录的文件权限
extern SUPERBLOCK sup;
void my_ls()
{
    display_dir(curDir);
}
void my_cd()
{
    string s;
    cin >> s;
    if (cd(curDir, s.c_str())) //进入目录成功
    {
        if (s == "..") //返回上一级目录
        {
            int pos;
            pos = path.find_last_of('/');
            path = path.substr(0, pos);
            if (path.size() == 0)
                path = "/";
        }
        else if (s == ".")
            path = path;
        else if (path == "/")
            path += s;
        else
            path += "/" + s;
    }
}
void my_mkdir()
{
    string s;
    cin >> s;
    if (isRoot == 0 && dirOwner == 1) //普通用户无法修改root用户的文件
        cout << "权限不够，请提升权限" << endl;
    else
        mkdir(curDir, s.c_str());
}
void my_mkfile()
{
    string s;
    cin >> s;
    if (isRoot==0 && dirOwner==1)
        cout << "权限不够，请提升权限" << endl;
    else
        mkfile(curDir, s.c_str());
}
void my_reformat()
{
    string s;
    if (isRoot==0)
        cout << "权限不够，请提升权限" << endl;
    else
        reformat();
}
void my_rm()
{
    string s;
    cin >> s;
    if (isRoot==0&&dirOwner==1)
        cout << "权限不够，请提升权限" << endl;
    else
        rm(curDir, s.c_str());
}
void my_sup()
{
    cout << "blocknum=" << sup.block_num << endl;
    cout << "blockremain=" << sup.block_remain << endl;
    cout << "blockuse=" << sup.block_use << endl;
    cout << "blocksize=" << sup.block_size << endl;
}
void my_chmod()
{
    string s;
    if (isRoot == 0)
    {
        cout << "权限不够，请提升权限" << endl;
        getline(cin, s);
    }
    else
    {
        int pride;
        cin >> s >> pride;
        chmod(curDir, s.c_str(), pride);
    }
}
void my_sudo()
{
    string pass;
        cout << "please input password: ";
        cin >> pass;
        if (strcmp(pass.c_str(), PWD) == 0)
        {
            isRoot=1;
            username = "root";
        }
        else
            cout << "wrong password" << endl;
}
void my_write()
{
    string s;
    cin >> s;
    getchar();
    DIRENTRY entry;
    if (namei(curDir, s.c_str(), entry))
    {
        if(isRoot==0&&entry.pride==1)
        {
            cout<<"权限不够"<<endl;
            return;
        }
        if (entry.kind == 'f')
        {
            char c;
            cout << "please input string:(end with \"ctrl+d\")" << endl;
            vector<char> v;
            while ((c = getchar()) != EOF)
                v.push_back(c);
            entry.fileSize = v.size();
            modifyEntry(curDir, s.c_str(), entry);
            fileWrite(entry.blockNum, v, entry.fileSize);
        }
        else
            cout << "file is a dir" << endl;
    }
    else
        cout << "file " << s << " doesn't exist" << endl;
}
void my_cat()
{
    string s;
    cin >> s;
    vector<char> v;
    DIRENTRY entry;
    if (namei(curDir, s.c_str(), entry))
    {
        if (entry.kind == 'd')
            cout << entry.name << " is dir" << endl;
        else
        {
            fileRead(entry.blockNum, v, entry.fileSize);
            string text;
            for (int i = 0; i < v.size(); i++)
                text.push_back(v[i]);
            cout << text <<endl;
        }
    }
    else
        cout << "file " << s << " doesn't exist" << endl;
}
void my_logout()
{
    isRoot = 0;
    username = USER;
}
void my_help()
{
    cout << "ls \t\t:获取当前目录下的文件" << endl;
    cout << "cd \"file\" \t:进入目录" << endl;
    cout << "mkdir \"file\" \t:创建目录文件" << endl;
    cout << "mkfile \"file\" \t:创建普通文件" << endl;
    cout << "rm \"file\" \t:删除文件" << endl;
    cout << "write \"file\" \t:写数据到文件中" << endl;
    cout << "cat \"file\" \t:读指定文件的数据" << endl;
    cout << "sudo  \t\t:获取超级权限" << endl;
    cout << "logout \t\t:退出超级用户" << endl;
    cout << "sup \t\t:查看超级块的数据" << endl;

    cout << "(sudo)reformat \t:格式化文件系统" << endl;
    cout << "(sudo)chmod \"file\" \"pride\" \t:改变文件权限" << endl;
}
