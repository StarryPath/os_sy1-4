#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

int fq_num[20]= {0,1,2,3,4,5,6,7,8,9};
int fq_size[20]={0};
int fq_addr[20]={0};
int fq_state[20]= {0};
int len=10;
void mm_init()            //��ʼ��
{
    srand((unsigned)time(NULL));
    fq_addr[0]=0;
    for(int i=0;i<len;i++)             //��������ڴ��С
    {
        fq_size[i]=rand()%1025;
        fq_addr[i+1]=fq_addr[i]+fq_size[i];
        if(i%2==0)
        {
            fq_state[i]=1;
        }
        else
            fq_state[i]=0;
    }
}
void show()             //��ʾ�ڴ�ʹ�����
{
    printf("-----------------------------------------------------\n");
    printf("|  ������  |  ������С(KB) |  ����ʼַ(K)  |  ״̬  |\n");
    printf("-----------------------------------------------------\n");
    char state_str[10];
    for(int i=0; i<len; i++)
    {
        if(fq_state[i]==0)
            strcpy(state_str,"����");
        else
            strcpy(state_str,"��æ");
        printf("|%10d|%15d|%15d|%8s|\n",fq_num[i],fq_size[i],fq_addr[i],state_str);
    }
    printf("-----------------------------------------------------\n");
}
void fgnc(int i,int n)        //�ָ��ڴ�
{
    for(int t=len; t>i+1; t--)
    {
        fq_size[t]=fq_size[t-1];
        fq_addr[t]=fq_addr[t-1];
        fq_num[t]=fq_num[t-1]+1;
        fq_state[t]=fq_state[t-1];
    }
    fq_size[i+1]=fq_size[i]-n;
    fq_addr[i+1]=fq_addr[i]+n;
    fq_state[i+1]=0;
    fq_num[i+1]=i+1;
    fq_size[i]=n;
    len++;

}
//void hbnc()
void mm_request(int n,int sel)
{
    if(sel==0)//FF�״���Ӧ
    {
        int j=0;
        for(int i=0; i<len; i++)
        {
            if(n<=fq_size[i]&&fq_state[i]==0)
            {
                fq_state[i]=1;
                printf("�����ڴ�ɹ�\n");
                if(n<fq_size[i])
                {
                    fgnc(i,n);
                }
                j=1;
                break;
            }
        }
        if(j==0)
            printf("�����ڴ�ʧ��\n");
    }
    if(sel==1)//BF �����Ӧ
    {
        int t=-1;
        int q;
        int l=0;
        int flag=1;
        for(int i=0; i<len; i++)  //������С�Ŀ��п�
        {
            if(n<=fq_size[i]&&l==0&&fq_state[i]==0)
            {
                t=fq_size[i];
                q=i;
                l=1;
            }
            if(fq_size[i]<t&&l==1&&fq_state[i]==0&&fq_size[i]>=n)
            {
                t=fq_size[i];
                q=i;
            }
        }
        if(t==-1)
        {
            printf("�����ڴ�ʧ��\n");
        }
        else
        {
            for(int i=0;i<len;i++)           //����Ƚϴ���
            {
                if(fq_size[i]<t&&fq_state[i]==0)
                    flag++;
            }

            if(n<fq_size[q])
            fgnc(q,n);
            fq_state[q]=1;
            printf("�����ڴ�ɹ���������%d��\n",flag);
        }


    }
    if(sel==2)//WF    ���Ӧ
    {
        int t=-1;
        int q=0;
        int l=0;
        for(int i=0; i<len; i++)
        {
            if(n<=fq_size[i]&&l==0&&fq_state[i]==0)
            {
                t=fq_size[i];
                q=i;
                l=1;
            }
            if(fq_size[i]>t&&l==1&&fq_state[i]==0)
            {
                t=fq_size[i];
                q=i;
            }
        }
        if(t==-1)
        {
            printf("�����ڴ�ʧ��\n");
        }
        else
        {
            if(n<fq_size[q])
            fgnc(q,n);
            fq_state[q]=1;
            printf("�����ڴ�ɹ�\n");
        }
    }
}
void mm_release(int n) //�ڴ��ͷ�
{
    int flag=0;
    if(fq_state[n+1]==0&&n<len-1)       //�����ͷ��ڴ�������·��Ƿ���У�������ϲ�
    {
        fq_size[n]=fq_size[n]+fq_size[n+1];
        fq_state[n]=0;

        for(int t=n+1;t<len-1;t++)
        {
            fq_addr[t]=fq_addr[t+1];
            fq_size[t]=fq_size[t+1];
            fq_num[t]=fq_num[t+1]-1;
            fq_state[t]=fq_state[t+1];
        }
        len--;
        flag++;
    }
    if(fq_state[n-1]==0&&n>0)           //�����ͷ��ڴ�������Ϸ��Ƿ���У�������ϲ�
    {
        fq_size[n-1]=fq_size[n-1]+fq_size[n];
        for(int t=n;t<len-1;t++)
        {
            fq_addr[t]=fq_addr[t+1];
            fq_size[t]=fq_size[t+1];
            fq_num[t]=fq_num[t+1]-1;
            fq_state[t]=fq_state[t+1];
        }
        len--;
        flag++;
    }
    if(flag==0)
    {
        printf("�ڴ��ͷ�ʧ��\n");
    }
    else
        printf("�ڴ��ͷųɹ�\n");
}
void shell()
{
    show();
    while(1)
    {

        char t='>';
        printf("%c",t);
        char s1[5]="";
        int s2;
        int s3;
        scanf("%s",s1);
        if(s1[0]=='r'&&s1[1]=='e'&&s1[2]=='q')         //��ʽ��req �ڴ��С  ������ ��0 1 2->FF BF WF)
        {
            scanf("%d",&s2);
            scanf("%d",&s3);
            mm_request(s2,s3);
            show();
        }
        else if(s1[0]=='r'&&s1[1]=='e'&&s1[2]=='l')    //��ʽ��rel ������
        {
            scanf("%d",&s3);
            mm_release(s3);
            show();
        }

        else
        {
            printf("%s","input error\n");
        }
    }
}
int main()
{
    mm_init();
    shell();
    return 0;
}
