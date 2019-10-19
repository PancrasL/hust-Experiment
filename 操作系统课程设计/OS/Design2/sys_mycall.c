asmlinkage int sys_mycall(const char *src_file, const char *dest_file)
{
    int src = sys_open(src_file, O_RDONLY, 0);
    if (src < 0) //打开源文件失败
    {
        return -1;
    }
    int dest = sys_open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest < 0) //打开目标文件失败
    {
        sys_close(src);
        return -2;
    }
    char buff[1024]; //缓冲区
    mm_segment_t fs;
    fs = get_fs();
    set_fs(get_ds());//限制访问范围（该用户空间）
    int i = 1;
    while (i)
    {
        i = sys_read(src, buff, 1024);
        if (i < 0) //读取文件失败
        {
            sys_close(src);
            sys_close(dest);
            set_fs(fs);
            return -3;
        }
        int state = sys_write(dest, buff, i);
        if (state < 0) //写入文件失败
        {
            sys_close(src);
            sys_close(dest);
            set_fs(fs);
            return -4;
        }
    }
    sys_close(src);
    sys_close(dest);
    set_fs(fs);
    return 1;
}
