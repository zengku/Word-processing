#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100
//#define MAXCNT  20 
#define BUFLEN  124

int main()
{

    FILE *fp;
    char buf[BUFLEN];
    int i, j;
    int n, m, k;
    char *delim = ",. ";
    char *p;

    int len = 0, f = 0, t = 0;
    char *arr[MAXLINE];
    
    /* 读文件 */
    fp = fopen("input.txt", "r");
    if (!fp) {
        return -EOF;
    }

    /* 复制内容 */
    while (fgets(buf, BUFLEN, fp)) {
        len = strlen(buf);
        arr[f] = (char *)malloc(len + 1);
        if (!arr[f]) {
            break;
        } 

        /* 去除符号 */
        p = strtok(buf, delim);
        while (p != NULL) {
            printf("%s\n", p);
            p = strtok(NULL, delim);
            if (p == NULL) {
                break;
            }
        }

         strcpy(arr[f++], buf);
    }

    fclose(fp);
 
    /* 去重 */
    for (n = 0; n < len - 1; n++) {
        for (m = n + 1; m < len; m++) {
            if (arr[m] == arr[n])
            arr[m] = '*';
            for (n = 0, m = 0; n < len; i++) {
                if (arr[n] != '*') {
                    arr[m] = arr[n];
                    m++;
                }
                arr[m] = '\0';
                printf("%s\n", arr[f]);
            }
        }
    }

/*   char *temp;
    for (i = 0; i < f; i++) {
        for (j = i + 1; j < f - i - 1; j++) {
            if (strcmp(arr[f], arr[f + 1]) > 0) {
                strcpy(temp, arr[f]);
                strcpy(arr[f],arr[f + 1]);
                strcpy(arr[f + 1], temp);
            }
        }
    }
 */

    // f--;
    // while (f > 0 && arr[f]) {
    //     printf("%s\n", arr[f--]);
    // }

    // for (t; t < f; t++) {
    //     printf("%s\n", arr[f++]);
    // }

    return 0;
}

