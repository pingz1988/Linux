## tips

* 利用无符号的溢出  
在size大小为2^n次幂的循环队列中，求队列头尾间的距离或队列中有多少元素时，可直接相减（tail-head），然后强转为无符号类型。 
* 用与运算替代求模运算，提高运行效率  
在size大小为2^n次幂的循环队列中，计算当前插入操作后队列的位置，直接用 in & (size-1)  

* 结构体赋值  
利用memcpy()  

* 动态内存分配  
malloc()后需memset()初始化内存，或者用calloc()  

* 字符串处理  
可用 sscanf、scanf、fscanf 函数对字符串作简单的处理，比如类似正则匹配的操作：  
```c
int k;
sscanf( "AAA123BBB456" , "%*[^0-9]%i" , &k)；  // 过滤掉字符串中的数字。k要取地址，执行后，k=123

char buf[512] = {0};
sscanf( "12345helloWORLD" , "%*[1-9]%[a-z]" , buf)；  // %*[1-9]表示过滤掉数字1-9，然后取小写字符串给buf，buf 为 hello

int a, b, c;
sscanf("2006:03:18", "%d:%d:%d", a, b, c); // 分隔字符串

char sztime1[16] = "", sztime2[16] = "";
sscanf("2006:03:18 - 2006:04:18", "%s - %s", sztime1, sztime2);  // 分隔字符串

// --------------------------------------------------------------------------------
#include <stdio.h>
#include <errno.h>
int main()
{
        char *p;
        int n;

        errno = 0;
        n = scanf("%m[0-7]", &p);  // 动态分配p的内存大小，并指定每个字符的范围只能是字符0~7
        if (n == 1) {
                printf("read: %s\n", p);
                free(p);
        } else if (errno != 0) {
                perror("scanf");
        } else {
                fprintf(stderr, "No matching characters\n");
        }

        return 0;
}
```
