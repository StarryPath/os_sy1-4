#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct d
{
    int PID;  //进程ID
    char Pname[5]; //进程名

    int other_data;    //RCB资源

    int state;  //进程状态   就绪0 运行1 阻塞2

    int *p_state; //状态队列链表指针

    int priority; //优先级
} d;
typedef struct PCB//PCB
{
    d data;

    struct PCB * father; //本进程的父进程
    struct PCB * son;   //本进程的子进程
    struct PCB *next;
} PCB,*PPCB;
PCB p[10];
int now_run;
typedef struct RCB //RCB
{
    int RID;
    int state;  //资源状态 0可用 1不可用
    PPCB L;     //头指针
} RCB,*PRCB;
RCB R[10]= {-1,0,NULL};
void cr_wl(PPCB &L) //建立等待队列的头结点
{
    PPCB s;
    s=(PPCB)malloc(sizeof(PCB));
    s->next=NULL;
    L=s;
}
void cr_pcb(char* s2,int s3,int len)
{

    strcpy(p[len].data.Pname,s2);
    p[len].data.priority=s3;
    p[len].data.state=0;
    p[len].data.PID=len;

}
void request(int n,int t)
{
    R[n].RID=n;
    if(R[n].L==NULL)
    {
        cr_wl(R[n].L);
    }

        PPCB s,q;
        q=(PPCB)malloc(sizeof(PCB));
        s=R[n].L;
        while(s->next!=NULL)
        {
            s=s->next;
        }

        s->next=q;
        q->next=NULL;
        q->data.PID=t;
        p[t].data.state=2;
        p[t].data.other_data=n;


}
void release(int n)
{
    PPCB s=R[n].L;
    int t=s->next->data.PID;
    p[t].data.state=0;
    p[t].data.other_data=-1;
    R[n].L->next=s->next->next;

}
void del_pcb(char* s2,int len)
{
    for(int i=1;i<=len;i++)
    {
        if(strcmp(p[i].data.Pname,s2)==0)
        {
            if(p[i].data.state==2)
            {
                release(p[i].data.other_data);
            }
            p[i].data.state=-1;

        }
    }
}
void scheduler(int len)
{

     int temp=0;
     for(int i=0; i<len; i++)
     {
         if((p[temp].data.priority<p[i+1].data.priority)&&((p[i+1].data.state==0)||(p[i+1].data.state==1)))//取最高优先级且非阻塞态的PID
         {
             temp=i+1;
         }
         if(p[i+1].data.state==2)
         {
             printf("*process %s is blocked;",p[i+1].data.Pname);
         }
     }
     printf("*process %s is running\n",p[temp].data.Pname);
     now_run=p[temp].data.PID;


}
void shell()
{

    int len=0;
    char init[5]="init";
    cr_pcb(init,0,len); //创建init进程
    while(1)
    {

        char t='>';
        printf("%c",t);
        char s1[5]="";
        char s2[5]="";
        int s3;
        scanf("%s",s1);
        if(s1[0]=='c'&&s1[1]=='r')
        {
            scanf("%s",s2);
            scanf("%d",&s3);
            len++;
            cr_pcb(s2,s3,len);
            scheduler(len);

        }
        else if(s1[0]=='r'&&s1[1]=='e'&&s1[2]=='q')
        {
            scanf("%d",&s3);
            request(s3,now_run);
            scheduler(len);
        }
        else if(s1[0]=='r'&&s1[1]=='e'&&s1[2]=='l')
        {
            scanf("%d",&s3);
            release(s3);
            scheduler(len);
        }
        else if(s1[0]=='d'&&s1[1]=='e'&&s1[2]=='l')
        {
            scanf("%s",s2);
            del_pcb(s2,len);
            scheduler(len);

        }
        else
        {
            printf("%s","input error\n");
        }
    }
}
int main()
{
    shell();
    return 0;
}



















