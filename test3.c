#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN sizeof(mywd_t)

typedef struct myword {
    int     num;            /* ���ָ��� */
    char    *word;          /* ���ֵ��� */
    struct  myword  *next;    
}mywd_t, *pmywd;

void main(void)
{   
    void print_link_to_file(pmywd head);   /* ��������ļ� */      
    pmywd find_words(FILE *input);         /* ��������������� */
    void destory_word(pmywd head);		   /* ���������ͷ��ڴ� */

    char infile_name[] = {"input.txt"};
    pmywd head;
    FILE *input;
    
    input = fopen(infile_name, "r");                  
    if (input == NULL) {
        printf("���ļ�%sʧ��\n", infile_name);
        exit(0);
    }
    
    head = find_words(input);       /* �ҵ��� */                 
    fclose(input);                                   
    print_link_to_file(head);       /* ������������ļ� */                  
    destory_word(head);
}

void print_link_to_file(pmywd head)
{
    /* �����������������������input.txt */ 
    printf("NOW,print LINK  to File......\n");
    pmywd p;
    FILE *output;
    char outfile_name[] = {"output.txt"};
    output = fopen(outfile_name, "w");

    if (output == NULL) {
        printf("���ļ�%sʧ��\n", outfile_name);
        exit(0);
    }
    p = head->next;
    do {
        fprintf(output,"%s,%d\n", p->word, p->num);
        p = p->next;
    } while(p != NULL);
    
    fclose(output);
    printf("print to file Done!\n");
}
 
pmywd new_word(char word[]) 
{
    /* ����һ���������飬����һ��myword�ṹ�� */
    pmywd tmp;
    char *t_word;
    /* ��һ���µĽڵ�����ռ� */
    tmp = (pmywd) malloc(LEN);        
    /* ��̬����һ���ռ�������myword->word����Ϊ�Ȿ���Ǹ�ָ�룬��Ҫָ��һ������������ */
    t_word = (char *) malloc(strlen(word));
    strcpy(t_word, strlwr(word));
    tmp->word = t_word;
    tmp->num = 1;
    tmp->next = NULL;

    return tmp;
}

pmywd instert_word(pmywd tmp, pmywd head)
{
    pmywd cur;

    if (head == NULL) {
        head = (pmywd) malloc(LEN);
        head->next = tmp;
    } else {
        cur = head->next;
        while (cur != NULL) {
            if (strcmp(tmp->word, cur->word) < 0) {
                /* С�ڵ�һ��ֵ ,��Ϊ������������ȵ�һ��С���Ǿ�����С�� */
                tmp->next = cur;
                head->next = tmp;
                break;
            } else if (strcmp(tmp->word, cur->word) == 0) {
                /* ���ڵ�ǰֵ */
                cur->num++;
                free(tmp);        
                break;
            } else if (strcmp(tmp->word, cur->word) > 0) {   
                /* ���ڵ�ǰֵ */ 
                if (cur->next != NULL) {
                    /* ���治Ϊ�� */ 
                    if (strcmp(tmp->word, cur->next->word) < 0) {
                        /* С����һ��ֵ ,���뵱ǰ�ڵ�֮�� */ 
                        tmp->next = cur->next;
                        cur->next = tmp;
                        break; 
                    }
                    /* ���ڵ�����һ��ֵ */ 
                    cur = cur->next;
                } else {
                    /* ����Ϊ�� */ 
                    cur->next = tmp; 
                    break; 
                }
            } 
        }
    }

    return head;
}
 
pmywd find_words(FILE *input)
{
    printf("start find Words....\n");
    pmywd head, tmp;
    pmywd instert_word(pmywd tmp, pmywd head); 	 /* ����ڵ� */
    pmywd new_word(char word[]);  				 /* ����һ���µĽڵ㣬����ָ�� */
    char ch;
    char word[25];
    int i = 0;
    head = NULL;
    
    while (!feof(input)) {
        ch = fgetc(input);
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
            word[i] = ch;
            i++;
        } else {
            word[i] = '\0';
            if (strlen(word) !=0) {
                tmp = new_word(word);
                head = instert_word(tmp, head);
            }   
            i = 0;
        }
    }
    printf("find Words Done!\n");

    return head;
}

void destory_word(pmywd head)
{
    printf("start free!\n");
    pmywd tmp;
    while (head != NULL) {
        tmp = head;
        head  = head->next;
        free(tmp);
    }
    printf("Free Done!\n");
} 

