#include<stdio.h>

struct process{
    int at;     // arrival time
    int bt;     // burst time
    int ct;     // completion_time
    int tat;    // turn around time
    int wt;     // waiting time
    int flag;
}p[10], temp[10];

void round_robin(int n, int q);
void sort_process_at(int n);
void insert(int n);
int delete();

// ready queue
int queue[100];
int front = -1;
int rear = -1;

float total_tat = 0;
float total_wt = 0;

int main()
{
    int n, q;
    scanf("%d", &n);
    scanf("%d", &q);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
    }
    
    round_robin(n, q);
    
    printf("%.2f", total_wt/n);
    
    return 0;
}

void round_robin(int n, int q)
{
    struct process temp[10];
    int exist[10] = {0};
    int curr_time = 0, diff=0;
    int i;
    
    sort_process_at(n);
    
    for(int j=0; j<n; j++)
    {
        temp[j]=p[j];
    }
    
    diff = temp[0].at - 0;
    
    insert(0);
    exist[0] = 1;
    
    while(front<=rear)
    {
        i=delete();
        if(temp[i].bt >= q)
        {
            temp[i].bt = temp[i].bt-q;
            curr_time += q;
        }
        else
        {
            curr_time += temp[i].bt;
            temp[i].bt=0;
        }
        
        for(int j=0; j<n; j++)
        {
            if(temp[j].at <= curr_time && exist[j]==0)
            {
                insert(j);
                exist[j]=1;
            }
        }
        
        if(temp[i].bt == 0 && temp[i].flag != 1)
        {
            p[i].ct = curr_time + diff;
            temp[i].flag = 1;
        }
        else
        {
            insert(i);
        }
        
    }
    
 
    for(int j=0; j<n; j++)
    {
        p[j].tat = p[j].ct - p[j].at;
        total_tat += p[j].tat;
        p[j].wt = p[j].tat - p[j].bt;
        total_wt += p[j].wt;
    }
    
}

void insert(int n)
{
    if(front==-1)
        front=0;
    rear++;
    queue[rear]=n;
}

int delete()
{
    int n;
    n = queue[front];
    front++;
    return n;
}


void sort_process_at(int n)
{
    struct process temp;
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            if(p[j].at > p[j+1].at)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}