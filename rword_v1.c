#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100
//#define MAXCNT  20 
#define BUFLEN  124

int main()
{

    FILE* fp;
    char buf[BUFLEN];
    int i, j;
    int n, m, k;
    const char* delim = ",. \n";
    char* p;

    int len = 0, f = 0, t = 0;
    char* arr[MAXLINE];
    char* tmp;
    /* 读文件 */
    fp = fopen("C:\\Users\\hp\\Desktop\\words\\input.txt", "r");
    if (!fp) {
        return -EOF;
    }

    /* 复制内容 */
    while (fgets(buf, BUFLEN, fp)) {
        /*len = strlen(buf);
        arr[f] = (char*)malloc(len + 1);*/
        /*if (!arr[f]) {
            break;
        }*/
        
        /* 去除符号 */
        p = strtok(buf, delim);
        while (p != NULL) {
            len = strlen(p);
            arr[f] = (char*)malloc(len + 1);
            strcpy(arr[f++], p);
            p = strtok(NULL, delim);
            if (p == NULL) {
                break;
            }
        }
    }

    fclose(fp);

    

    /**************排序******************/
    for (int i = 0; i < f; i++)
    {
        for (int j = i+1; j < f; j++)
        {
            if(strcmp(arr[i],arr[j])>0){
                tmp=arr[i];
                arr[i]=arr[j];
                arr[j]=tmp;
            }
        }
    }
    for (int i = 0; i < f; i++)
    {
        printf("%s\n", arr[i]);
    }
    /**************去重******************/
    
    return 0;
}
