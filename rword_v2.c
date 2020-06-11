#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN sizeof(struct mywd)

struct mywd {
    int     num;
    char    *word;
    struct mywd *next;
};

void main(void) 
{
    struct mywd *head;
    struct mywd *tmp;
    FILE *rword;

    /* 打开文件 */
    rword = fopen("input.txt", "r");
    if (rword == NULL) {
        printf("文件打开失败");
        return -EOF;
    }

    struct mywd *cur;
    if (head == NULL) {
        head = (struct mywd *) malloc(LEN);
        head->next = tmp;
    } else {
        cur = head->next;
        while (cur != NULL)
        {
            if (strcmp(tmp->word, cur->word) < 0) {
                tmp->next = cur;
                head->next = tmp;
                break;
            } else if (strcmp(tmp->word, cur->word) == 0) {
                cur->num++;
                free(tmp);
                break;
            } else if (strcmp(tmp->word, cur->word) > 0) {
                if (cur->next != NULL) {
                    if (strcmp(tmp->word, cur->next->word) < 0) {
                        tmp->next = cur->next;
                        cur->next = tmp;
                        break;
                    }
                    cur = cur->next;
                } else {
                    cur->next = tmp;
                    break;
                }
            }
        }
    }
    




}