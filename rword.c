#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define BUFLEN  1024

int mycmp(const void *p1, const void *p2)
{
    return strcmp(*(char *const *)p1, *(char *const *)p2);
}

int main()
{
    char buf[BUFLEN];
    int len = 0, f = 0;
    char *arr[MAXLINE];
    FILE *rfile;
    
    /* 读文件 */
    rfile = fopen("input.txt", "r");
    if (!rfile) {
        return -EOF;
    }

    /* 复制文件 */
    while (fgets(buf, BUFLEN, rfile)) {
        len = strlen(buf);
        arr[f] = (char *)malloc(len + 1);
        if (!arr[f]) {
            break;
        } 
        strcpy(arr[f++], buf);
    }

    fclose(rfile);

    char *temp;
    for (int i = 0; i < f; i++) {
        for (int j = i + 1; j < f - i - 1; j++) {
            if (mycmp(arr[i], arr[j]) > 0) {
                strcpy(temp, arr[i]);
                strcpy(arr[i],arr[j]);
                strcpy(arr[j], temp);
            }
        }
    }

    f--;
    while (f >= 0 && arr[f]) {
        printf("%s\n", arr[f--]);
    } 


    // int h = 0;
    // qsort(arr, f, sizeof(char), mycmp);
    // for (h = 0; h < f; h++) {
    //     printf("%s", arr[f]);
    // }


    return 0;
}

