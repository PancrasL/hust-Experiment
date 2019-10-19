#include "blockManage_layer.h"
BITBLOCK bitB;  //位视图块在内存中的拷贝
SUPERBLOCK sup; //超级块在内存中的拷贝

int block_write(int blockNum, void *fb) //向块blockNum中写入以fb开始，长度为BLOCK_SIZE字节的数据
{
    FILE *fp;
    if ((fp = fopen(fileSystemPath, "rb+")) != NULL)
    {
        fseek(fp, blockNum * BLOCK_SIZE, SEEK_SET); //定位到该块的起始位置
        fwrite(fb, sizeof(FILEBLOCK), 1, fp);       //写入该块
        fclose(fp);                                 //关闭文件
        return true;
    }
    return false;
}
int block_read(int blockNum, void *fb) //将块blockNum中的数据读取到以fb开始，长度至少为BLOCK_SIZE字节的缓冲区中
{
    FILE *fp;
    if ((fp = fopen(fileSystemPath, "rb")))
    {
        fseek(fp, blockNum * BLOCK_SIZE, SEEK_SET); //定位到该块的起始位置
        fread(fb, sizeof(FILEBLOCK), 1, fp);        //写入该块
        fclose(fp);                                 //关闭文件
        return true;
    }
    return false;
}
int get_block() //获取空闲块
{
    if (sup.block_remain == 0)
        return -1;         //没有空闲块了
    if (sup.free_num == 0) //提取出来的空闲块用完了
    {
        for (int i = 0; i < BLOCK_SIZE; i++) //顺序扫描一遍位试图，提取出最多10个空闲块
            if (bitB.bitmap[i] == 0)         //块i是空闲的
            {
                sup.free_block[sup.free_num++] = i;
                bitB.bitmap.set(i);
                if (sup.free_num == 10)
                    break; //获取10个空闲块后跳出循环
            }
        block_write(1, &bitB); //将更改后的空闲块写入磁盘
    }
    sup.block_remain--;
    sup.block_use++;
    int num = sup.free_block[--sup.free_num];
    block_write(0, &sup); //将更改后的超级块写入磁盘
    cout<<"block "<<num<<" get success"<<endl;
    if(num<3)
        return -1;
    return num;           //返回一个空闲块号
}
void free_block(int blockNum) //回收空闲块
{
    if (blockNum <= 2)
    {
        printf("第0块和第1块和第2块不可释放\n");
        return ;
    }
    if(bitB.bitmap[blockNum]==0)
    {
        cout<<"block "<<blockNum<<" is already free"<<endl;
        return ;
    }
    /*修改超级块*/
    sup.block_remain++;
    sup.block_use--;
    /*修改位视图块*/
    bitB.bitmap.reset(blockNum); //标记该块为空闲块
    /*将修改信息写入磁盘*/
    block_write(1, &bitB);
    block_write(0, &sup);
    cout<<"block "<<blockNum<<" free success"<<endl;
}
bool reformat() //格式化文件系统
{
    /*重置位视图块*/
    bitB.bitmap.reset();
    bitB.bitmap.set(0);
    bitB.bitmap.set(1);
    bitB.bitmap.set(ROOT_BLOCK_NUM); //第0块(超级块)、第1块(位视图块)和ROOT_BLOCK_NUM块被占用
    block_write(1, &bitB);
    /*重置超级块*/
    sup.block_size = BLOCK_SIZE;
    sup.block_num = BLOCK_NUM;
    sup.block_use = 3;
    sup.free_num = 0;
    sup.block_remain = BLOCK_SIZE - 3;
    block_write(0, &sup);
    /*创建根目录*/
    DIRBLOCK root;
    DIRENTRY temp;
    root.entryNum = 0;
    root.next = 0;
    /*创建本目录目录项*/
    strcpy(temp.name, ".");
    temp.kind = 'd';
    temp.blockNum = ROOT_BLOCK_NUM;
    temp.create_date = time(0);
    temp.fileSize=0;
    temp.pride=0;
    root.dirEntry[0] = temp;
    root.entryNum++;
    /*创建父目录目录项*/
    strcpy(temp.name, ".."); //根目录的父节点仍然是根目录
    temp.kind = 'd';
    temp.blockNum = ROOT_BLOCK_NUM;
    root.dirEntry[1] = temp;
    root.entryNum++;
    temp.create_date = time(0);
    block_write(ROOT_BLOCK_NUM, &root);
    return true;
}
void display_free_1()
{
    for (int i = 0; i < BLOCK_NUM; i++)
        if (bitB.bitmap[i] == false)
            cout << i << ' ';
    cout << endl;
}
void display_free_2()
{
    int i = sup.free_num - 1;
    while (i >= 0)
        cout << sup.free_block[i--] << ' ';
    cout << endl;
}
