# 文件输入/输出
## 文件间的通信
### 文件
一系列连续的字节，每个字节都能被单独读取
### 文件模式
1. 二进制模式
    - 可访问每个字节
2. 文本模式
    - 读取文件，把本地环境表示的行末尾或文件结尾映射为C模式
    - 以文本模式读取旧式Macintosh:\r ——> \n
    -  写入：\n ——> \r
### I/O级别
* 底层I/O
* 标准高级I/O(C标准支持)
### 标准文件
* 标准输入、标准输出、标准错误输出
* 标准输入：键盘……
* 标准输出，标准错误输出：显示……
## 标准I/O
    /* count.c -- using standard I/O */
    #include <stdio.h>
    #include <stdlib.h> // exit() prototype

    int main(int argc, char *argv[])
    {
        int ch;         // place to store each character as read
        FILE *fp;       // "file pointer"
        unsigned long count = 0;
        if (argc != 2)
        {
            printf("Usage: %s filename\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        if ((fp = fopen(argv[1], "r")) == NULL)
        {
            printf("Can't open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        while ((ch = getc(fp)) != EOF)
        {
            putc(ch,stdout);  // same as putchar(ch);
            count++;
        }
        fclose(fp);
        printf("File %s has %lu characters\n", argv[1], count)  ;
    
        return 0;
    }



### 检查命令行参数
* 字符串argv[0]为该程序的名称
* exit()函数关闭所有打开的文件并结束程序
    - 标准要求0 或 宏EXIT_SUCCESS用于表明文件结束，宏EXIT_FAILURE用于表示结束程序失败，原型都在stdlib.h中
### fopen()函数
fopen(待打开文件名称,模式字符串)
* 模式字符串
     - "r": 读模式打开
     - "w"：写模式打开，删除现有文件内容，若不存在，创建新文件
     - "a"：写模式，文末添加，若不存在，创建新文件
     - "r+"：更新模式：读写文件
     - "a+"：更新模式：文末添加，若不存在，创建新文件
     - "w+"：删除现有文件内容，若不存在，创建新文件
     - "rb"、"wb"、"ab"、"rb+"、"r+b"、"wb+"、"w+b"、"ab+"、"a+b"：二进制模式，非文本模式

成功打开后，返回文件指针，指向包含文件信息的数据对象，包含操作文件的I/O函数所用的缓冲区信息。
### getc(),putc()
ch=getc(fp);    //从fp指定的文件中获取一个字符

putc(ch,fpout);   //把字符串ch放入fpout指定的文件
### 文件结尾
* getc()返回EOF