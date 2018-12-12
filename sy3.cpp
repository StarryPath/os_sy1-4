#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#define F 3  //内存块数量
#define P 8//进程大小
#define L 20//页面走向长度
int M[F];   //物理块
int c1=0,c2=0,c3=0;
int RS[L]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};   //引用串
void init_first()
{
    srand((unsigned)time(NULL));
    for(int i=0; i<L; i++)
    {
        RS[i]=rand()%P;
    }
}
void init()
{

    for(int i=0; i<F; i++)
    {
        M[i]=-1;
    }
}
void show(int j)
{

    printf("%5d",RS[j]);
    for(int i=0;i<F;i++)
    {
        printf("%5d",M[i]);
    }
    printf("\n");
}
int jd(int i,int &re)//判断是否缺页 缺返回0 不缺返回1
{

    for(int j=0; j<F; j++)
    {
        if(RS[i]==M[j])
        {
            re=j;
            return 1;
        }
    }
    return 0;
}
int ym(int &re) //验满
{

    for(int j=0; j<F; j++)
    {
        if(M[j]==-1)
        {
            re=j;
            return 1;
        }
    }
    return 0;
}
void OPT()//最佳置换算法
{
    int ct=1;//缺页次数

    int temp;
    int f1;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("最佳置换算法\n");

    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {

            if(jd(i,re)==1) //不缺页
            {
                printf("%5d\n",RS[i]);
                continue;
            }
            else if(ym(re2)==1)
            {
                M[re2]=RS[i];

                ct++;
            }
            else   //缺页
            {
                int ff=0;
                int Q[F];//记录M[F]中每个M[]最近将要访问的位置
                for(int j=0;j<F;j++)
                {
                    for(int t=i+1;t<L;t++)//遍历还没被访问的页面值
                    {
                        if(M[j]==RS[t])//如果以后会被访问到
                        {
                            ff++;
                            Q[j]=t;
                            break;
                        }
                    }
                    if(ff==0)//以后不会被访问到
                    {
                        Q[j]=L;//设为最大值
                    }
                    ff=0;

                }
                temp=Q[0];
                f1=0;
                for(int j=1;j<F;j++)//取最大值
                {
                    if(temp<Q[j])
                    {
                        temp=Q[j];
                        f1=j;
                    }
                }
                M[f1]=RS[i];
                ct++;
            }

        show(i);
    }
    printf("缺页率为：%f\n",ct/1.0/L);
}
void FIFO()//先进先出
{
    int ct=1;
    int l=0;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("先进先出页面置换算法\n");
    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {
            if(jd(i,re)==1) //不缺页
            {
                printf("%5d\n",RS[i]);
                continue;
            }
            else if(ym(re2)==1)
            {
                M[re2]=RS[i];
                l=(re2+1)%F;
                ct++;
            }
            else   //缺页
            {
                M[l]=RS[i];
                l=(l+1)%F;
                ct++;
            }
        show(i);
    }
    printf("缺页率为：%f\n",ct/1.0/L);}
void LRU()//最近最久未使用
{
    int FW[F]={0};//上次被访问所经历的时间
    int ct=1;
    int f1=0;
    int temp;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("最近最久未使用页面置换算法\n");
    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {

        //物理块装满后

            if(jd(i,re)==1) //不缺页
            {
                for(int k=0;k<F;k++)
                {
                    if(M[k]!=-1)
                    FW[k]++;
                }
                FW[re]=0;
                printf("%5d\n",RS[i]);
                continue;
            }
            else if(ym(re2)==1)
            {
                for(int k=0;k<F;k++)
                {
                    if(M[k]!=-1)
                    FW[k]++;
                }

                M[re2]=RS[i];
                FW[re2]=0;
                ct++;
            }
            else   //缺页
            {

                temp=FW[0];
                f1=0;
                for(int k=1;k<F;k++)
                {
                    if(temp<FW[k])
                    {
                        temp=FW[k];
                        f1=k;
                    }
                }
                M[f1]=RS[i];
                for(int k=0;k<F;k++)
                {
                    FW[k]++;
                }
                FW[f1]=0;
                ct++;
            }
        show(i);


    }
    printf("缺页率为：%f\n",ct/1.0/L);

}
int main()
{
    //init();
//    for(int i=0; i<L; i++)
//    {
//        printf("%d ",RS[i]);
//
//    }
//    printf("%d ",M[2]);
//init_first();
init();
OPT();
init();
FIFO();
init();
LRU();
    return 0;
}
