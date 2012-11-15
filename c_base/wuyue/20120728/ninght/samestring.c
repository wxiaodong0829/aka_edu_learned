#include<stdio.h>
#include<string.h>
#define FLG 0
int main()
{
    int i, l; 
    int j = 0;
    int k = 0;
	int m = 10;
    char m_str[10]= "aabbccssss";
    char c[10][10];
	int len;
	int p;

	printf("%d\n", m);
    
    printf("%s\n", m_str);


    l=strlen(m_str);
    for(i = 0; m_str[i] != '\0'; i++)
    {
        if(m_str[i] == m_str[i + 1])
        {
            c[j][k++] = m_str[i];
        }else{
            c[j][k++] = m_str[i];
            c[j][k] = '\0';
            printf("%s\n", c[j]);
            j++; k = 0;
        }
    }
	len = strlen(c[0]);
	p = 0;
	while (j-- > 1) {
		if (len < strlen(c[j]))	{
			len = strlen(c[j]);
			p = j;
		}
	}
	printf("len = %d, %s\n", len, c[p]);


#if FLG
    for (i=0; k<=l; i++)
    {
        for (j=0; m_str[k]!='\0'; j++, k++)
            {
                if(m_str[k]==m_str[k+1])
                {
                    c[i][j]=m_str[k];
                }
                else {c[i][j]=m_str[k]; break;}
            }
        c[i][j]='\0';
        printf("%s\n", c[i]);
    }
#endif
            
    return 0;
}
