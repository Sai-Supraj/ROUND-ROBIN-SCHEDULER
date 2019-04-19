#include<stdio.h>
#include<stdlib.h>
void sorting();
struct process
{
	char id;
	int arival_time;
	int burst_time;
	int waiting_time;
	int remaining_time;
	int flag;
}p[10];

int n;
int sequence[10];
int seqcount=0;
int queue[10];
int front=-1,rear=-1;
void add_queue(int i)
{
    if(rear==10)
        printf("overflow");
    else{
           rear++;
           queue[rear]=i;
     if(front==-1)
            front=0;

    }

}

int pop_queue()
{
    int temp;
    if(front==-1)
        printf("underflow");
    else{
        temp=queue[front];
        front++;
        if(front > rear){
            front=rear=-1;
        }
    }
    return temp;
}
int checking(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(queue[k]==i)
        return 1;
    }
    return 0;
}



void main()
{
    int i,j,time=0,complete_burst=0,time_qu;
    char c='A';
    float average_waiting=0;
     printf("\t *****ENTER THE NUMBER OF PROCESSES GET INTO PROCESSING  : ");
     scanf("%d",&n);
     printf("\n\t *****ENTER THE ARRIVAL  TIME , BURST TIME  FOR ALL PROCESS SIMULTANEOUS :\n ");
     for(i=0;i<n;i++)
     {

         p[i].id=c;
         c=c+1;
         printf("\t\t");
         printf("\n\t\t****%d PROCESS  : ",i+1);
         scanf("%d %d",&p[i].arival_time,&p[i].burst_time);
         p[i].remaining_time=p[i].burst_time;
         p[i].flag=0;
         complete_burst+=p[i].burst_time;
    }
    printf("\n\t *****ENTER THE TIME QUANTUM  :");
    scanf("%d",&time_qu);
    sorting();
    add_queue(0);
    printf("\n\t ******GANTT CHART: ");

     if(p[0].arival_time==0){
        complete_burst=complete_burst-1;
     }
    for(time=p[0].arival_time;time<=complete_burst;)
    {
        i=pop_queue();
        if(p[i].remaining_time<=time_qu)
        {
            time+=p[i].remaining_time;
            p[i].remaining_time=0;
            p[i].flag=1;
            printf(" %c ",p[i].id);
            p[i].waiting_time=time-p[i].arival_time-p[i].burst_time;
            sequence[seqcount]=p[i].id;
            seqcount++;
            for(j=0;j<n;j++)
            {
                if(p[j].arival_time<=time && p[j].flag!=1&& checking(j)!=1)
                {
                    add_queue(j);
                }
            }
        }
        else
        {
            time+=time_qu;
            p[i].remaining_time-=time_qu;
            printf(" %c ",p[i].id);
            for(j=0;j<n;j++)
            {
                if(p[j].arival_time<=time && p[j].flag!=1 && i!=j && checking(j)!=1)
                {
                    add_queue(j);
                }
            }
            add_queue(i);
        }
     }

    printf("\n\n\t***SEQUENCE : ");
    for(int k=0;k<seqcount;k++){
        printf(" -> %c ",p[k].id);
    }

    printf("\n\n\t     PROCESS\tARRIVAL TIME\tBURST TIME\tWAITING TIME");
    for(i=0;i<n;i++)
    {
        average_waiting+=p[i].waiting_time;
        printf("\n\t     %c\t\t %d \t\t %d \t\t%d",p[i].id,p[i].arival_time,p[i].burst_time,p[i].waiting_time);
    }
    printf("\n\n\t ******Average waiting time:%f\n",average_waiting/n);
}
void sorting()
{
    struct process temp;
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].arival_time>p[j].arival_time)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}
