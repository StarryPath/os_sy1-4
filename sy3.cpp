#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#define F 3  //�ڴ������
#define P 8//���̴�С
#define L 20//ҳ�����򳤶�
int M[F];   //�����
int c1=0,c2=0,c3=0;
int RS[L]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};   //���ô�
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
int jd(int i,int &re)//�ж��Ƿ�ȱҳ ȱ����0 ��ȱ����1
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
int ym(int &re) //����
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
void OPT()//����û��㷨
{
    int ct=1;//ȱҳ����

    int temp;
    int f1;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("����û��㷨\n");

    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {

            if(jd(i,re)==1) //��ȱҳ
            {
                printf("%5d\n",RS[i]);
                continue;
            }
            else if(ym(re2)==1)
            {
                M[re2]=RS[i];

                ct++;
            }
            else   //ȱҳ
            {
                int ff=0;
                int Q[F];//��¼M[F]��ÿ��M[]�����Ҫ���ʵ�λ��
                for(int j=0;j<F;j++)
                {
                    for(int t=i+1;t<L;t++)//������û�����ʵ�ҳ��ֵ
                    {
                        if(M[j]==RS[t])//����Ժ�ᱻ���ʵ�
                        {
                            ff++;
                            Q[j]=t;
                            break;
                        }
                    }
                    if(ff==0)//�Ժ󲻻ᱻ���ʵ�
                    {
                        Q[j]=L;//��Ϊ���ֵ
                    }
                    ff=0;

                }
                temp=Q[0];
                f1=0;
                for(int j=1;j<F;j++)//ȡ���ֵ
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
    printf("ȱҳ��Ϊ��%f\n",ct/1.0/L);
}
void FIFO()//�Ƚ��ȳ�
{
    int ct=1;
    int l=0;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("�Ƚ��ȳ�ҳ���û��㷨\n");
    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {
            if(jd(i,re)==1) //��ȱҳ
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
            else   //ȱҳ
            {
                M[l]=RS[i];
                l=(l+1)%F;
                ct++;
            }
        show(i);
    }
    printf("ȱҳ��Ϊ��%f\n",ct/1.0/L);}
void LRU()//������δʹ��
{
    int FW[F]={0};//�ϴα�������������ʱ��
    int ct=1;
    int f1=0;
    int temp;
    int re=0;
    int re2;
    M[0]=RS[0];
    printf("������δʹ��ҳ���û��㷨\n");
    printf("    R   M[0] M[1] M[2]\n");
    show(0);
    for(int i=1; i<L; i++)
    {

        //�����װ����

            if(jd(i,re)==1) //��ȱҳ
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
            else   //ȱҳ
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
    printf("ȱҳ��Ϊ��%f\n",ct/1.0/L);

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
