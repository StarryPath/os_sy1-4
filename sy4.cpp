#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include<iostream>

using namespace std;
int m;//��Դ������
int n;//������
int  **Max; //����������
int* num_m; //��������Դʸ��
int **Allocation; //�������
int **Need; //�������
int *see; //��ȫ����
void init() //��ʼ����������Դʸ��������������
{
    printf("������Դ������\n");
    scanf("%d",&m);
    num_m=new int[m];

    printf("����ÿ����Դ������\n");
    for(int i=0; i<m; i++)
    {
        scanf("%d",&num_m[i]);
    }
    printf("���������\n");
    scanf("%d",&n);
    see=new int[n];
    Max=new int*[n];//����ָ�����飬����������
    for(int i=0; i<n; i++)
    {
        Max[i]=new int[m];
    }

    Allocation=new int*[n];//�������
    for(int i=0; i<n; i++)
    {
        Allocation[i]=new int[m];
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Allocation[i][j]=0;
        }
    }

    printf("����ÿ�����̶���Դ�����������\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("����Max[%d][%d]\n",i,j);
            scanf("%d",&Max[i][j]);
        }
    }
    Need=new int*[n];//����ָ������
    for(int i=0; i<n; i++)
    {
        Need[i]=new int[m];
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Need[i][j]=Max[i][j]-Allocation[i][j];
        }
    }
}
void show()
{
    printf("����������Ϊ��\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Max[i][j]);
        }
        printf("\n");
    }
    printf("�������Ϊ��\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Allocation[i][j]);
        }
        printf("\n");
    }
    printf("�������Ϊ��\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Need[i][j]);
        }
        printf("\n");
    }
    printf("��������Դʸ��Ϊ��\n");
    for(int i=0; i<m; i++)
    {
        printf("%d ",num_m[i]);
    }
    printf("\n");
}
int sec()
{
    int *temp=new int[m];

    for(int i=0;i<m;i++)
    {
        temp[i]=num_m[i];
    }
    for(int i=0; i<n; i++)
    {
        see[i]=0;
    }
    int flag=0;
    for(int k=0; k<n; k++)
    {

        for(int i=0; i<n; i++)
        {
            if(see[i]==0)
            {
                for(int j=0; j<m; j++)
                {
                    if(temp[j]>=Need[i][j])
                    {
                        flag++;
                    }
                }
                if(flag==m)//����
                {
                    see[i]=1;//��i�����̽��밲ȫ����
                    for(int j=0; j<m; j++)
                    {
                        temp[j]=temp[j]+Allocation[i][j];
                    }
                    flag=0;
                    break;
                }
                flag=0;
            }

        }
    }
    for(int i=0; i<n; i++)
    {

        if(see[i]==0)
        {
            return 0;//����ȫ
        }
    }
    return 1;//��ȫ
}
void req(int i,int j,int k)//i��ʾ����Pi,j��ʾ��ԴRj��k�����������
{
    if(k>Need[i][j])
    {
        printf("������Դ�������������������ֵ\n");
    }
    else
    {
        if(k>num_m[j])
        {
            printf("�����㹻��Դ\n");
        }
        else
        {
            num_m[j]=num_m[j]-k;
            Allocation[i][j]=Allocation[i][j]+k;
            Need[i][j]=Need[i][j]-k;
            if(sec()==1)
            {
                printf("����ɹ�\n");
            }
            else
            {
                num_m[j]=num_m[j]+k;
                Allocation[i][j]=Allocation[i][j]-k;
                Need[i][j]=Need[i][j]+k;
                printf("����ͨ����ȫ�Լ�⣬����ʧ��\n");
            }
        }
    }

}

void shell()
{
    while(1)
    {

        char t='>';
        printf("%c",t);
        char s1[5]="";

        int s2,s3,s4;
        scanf("%s",s1);
        if(s1[0]=='r'&&s1[1]=='e'&&s1[2]=='q')
        {
            scanf("%d %d %d",&s2,&s3,&s4);
            req(s2,s3,s4);
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

    init();
    show();
    shell();
    printf("%d %d",num_m[2],Max[1][1]);
    return 0;
}
