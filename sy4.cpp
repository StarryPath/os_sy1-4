#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include<iostream>

using namespace std;
int m;//资源种类数
int n;//进程数
int  **Max; //最大需求矩阵
int* num_m; //可利用资源矢量
int **Allocation; //分配矩阵
int **Need; //需求矩阵
int *see; //安全序列
void init() //初始化可利用资源矢量和最大需求矩阵
{
    printf("输入资源种类数\n");
    scanf("%d",&m);
    num_m=new int[m];

    printf("输入每种资源的数量\n");
    for(int i=0; i<m; i++)
    {
        scanf("%d",&num_m[i]);
    }
    printf("输入进程数\n");
    scanf("%d",&n);
    see=new int[n];
    Max=new int*[n];//开辟指针数组，最大需求矩阵
    for(int i=0; i<n; i++)
    {
        Max[i]=new int[m];
    }

    Allocation=new int*[n];//分配矩阵
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

    printf("输入每个进程对资源的最大需求数\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("输入Max[%d][%d]\n",i,j);
            scanf("%d",&Max[i][j]);
        }
    }
    Need=new int*[n];//开辟指针数组
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
    printf("最大需求矩阵为：\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Max[i][j]);
        }
        printf("\n");
    }
    printf("分配矩阵为：\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Allocation[i][j]);
        }
        printf("\n");
    }
    printf("需求矩阵为：\n");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            printf("%d ",Need[i][j]);
        }
        printf("\n");
    }
    printf("可利用资源矢量为：\n");
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
                if(flag==m)//成立
                {
                    see[i]=1;//第i个进程进入安全序列
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
            return 0;//不安全
        }
    }
    return 1;//安全
}
void req(int i,int j,int k)//i表示进程Pi,j表示资源Rj，k是申请的数量
{
    if(k>Need[i][j])
    {
        printf("所需资源数超过它所宣布的最大值\n");
    }
    else
    {
        if(k>num_m[j])
        {
            printf("尚无足够资源\n");
        }
        else
        {
            num_m[j]=num_m[j]-k;
            Allocation[i][j]=Allocation[i][j]+k;
            Need[i][j]=Need[i][j]-k;
            if(sec()==1)
            {
                printf("分配成功\n");
            }
            else
            {
                num_m[j]=num_m[j]+k;
                Allocation[i][j]=Allocation[i][j]-k;
                Need[i][j]=Need[i][j]+k;
                printf("不能通过安全性检测，分配失败\n");
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
