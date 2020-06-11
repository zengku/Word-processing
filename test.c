#include<stdio.h>
#include<string.h>
 
#define     MAX   100
 
int main()
{
    char str[MAX];
    char c;
    int strlen = 0;
    int i,j,k;
 
    scanf("%s",&str);//连续输入字符串
 
    for(i = 0;str[i] != '\0';i++);
 
    strlen = i;
 
    for(i = 0;i <= strlen - 1;i ++)
    {
        for(j = i + 1;j <= strlen - 1;j ++)
        {
            if(str[i] == str[j])
            {
              
                 for(k = j;k <= strlen - 1;k ++)
                 {
                    str[k]=str[k + 1];
                 }
                 strlen --;
                 j --;//避免出现多个相同字符连在一起时出错的问题
                
            }
            
        }
        
    }
 
    str[strlen] = '\0';
    
    printf("%s",&str);
    return 0;
}