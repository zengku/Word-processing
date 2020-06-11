#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100
#define BUFLEN  124

int main()
{

    FILE *rfp;
    FILE *wfp;
    char buf[BUFLEN];
    char *arr[MAXLINE];
    const char *delim = ",. \n";
    char *p;
    int len, f;     /* len 是 arr 长度，f 是 arr 个数 */   
    int i, j; 
    char *tmp;

    /* 读文件 */
    rfp = fopen("input.txt", "r");
    if (rfp == NULL) {
        printf("打开文件失败");
        return -EOF;
    }

    /* 复制内容 */
    len = 0;
    f = 0;
    while (fgets(buf, BUFLEN, rfp)) {       
        /* 去除符号 */
        p = strtok(buf, delim);
        while (p != NULL) {
            len = strlen(p);
            arr[f] = (char *)malloc(len + 1);
            strcpy(arr[f++], p);
            p = strtok(NULL, delim);
            if (p == NULL) {
                break;
            }
        }
    }

    fclose(rfp);
  
    /* 排序、去重 */
    int flag;
    int c = 1;
    int cnt[] = {0};

    for (i = 0; i < f; i++) {
        for ( j = i + 1; j < f; j++) {
            flag = 0;
            if (stricmp(arr[i], arr[j]) == 0) {
                flag += 1;
                arr[j] = '\0';   
            

            } else if (stricmp(arr[i], arr[j]) > 0) {  
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                flag = 1;
            } 
        }
    }
/*
    for(n--;n>=0;n--) { 
        if('z'>=juzi[n]&&juzi[n]>='a')//该字母du为小写
            cishu[juzi[n]-'a']++;//次数加dao1
        if('Z'>=juzi[n]&&juzi[n]>='A')//该字母为大写
            cishu[juzi[n]-'A']++;//次数加1
    }

    for(n=0;n<26;n++)//输出每个单词出现的次数
    {
        if(cishu[n]!=0)
            printf("%c:%d ",('a'+n),cishu[n]);
    }
*/

    /* 打印 */
    for (i = 0; i < f; i++) {
        printf("%s,\n", arr[i]);
    } 

    /* 写文件 */
    /* wfp = fopen("output.txt", "w");
    if (!wfp) {
        printf("写入文件失败");
        return -EOF;
    }

    for (i = 0; i < f; i++) {
        fprintf(wfp, "%s,\n", arr[i]);
    }    
    fclose(wfp);
    */

    //printf("%d\n", flag);

    /* 去重 */
    // int n, m, flag;
    // m = 1;
    // k = 0;
    // for (n = 0; n < f; n++) {
    //     if (stricmp(arr[n], arr[n++]) == 0) {
    //         arr[n] = arr[n++];
    //         arr[n++] = '\0';
    //         k = f - 1;
    //         m++;
    //     }
    // }






    return 0;
}
