#include<stdio.h>

struct process{
    int at;     // arrival time
    int bt;     // burst time
    int ct;     // completion time
    int tat;    // turn around time
    int wt;     // waiting time
    int flag; 
}p[20];

void FCFS(int n);
void sort_process_at(int n);
void SJF(int n);
void sort_process_bt(int s, int n);
void SRTN(int n);

float total_tat;
float total_wt;

int main()
{
    int choice, n;
    scanf("%d", &choice);
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
    }
    switch(choice)
    {
        case 1:
            FCFS(n);
            break;
        case 2:
            SJF(n);
            break;
        case 3:
            SRTN(n);
            break;
        default:
            printf("\nInvalid Choice!\n");
    }
    
    printf("%.2f %.2f", total_wt/n, total_tat/n);
    
    return 0;
}

void FCFS(int n)
{
    // sort process according to arrival time
    sort_process_at(n);
    
    // calculate completion time
    p[0].ct = p[0].bt + p[0].at;
    for(int i=1; i<n; i++)
    {
        p[i].ct = p[i-1].ct + p[i].bt;
        
        // for late arrival process (maintains idol state)
        if(p[i].at > p[i-1].ct)
        {
            p[i].ct += (p[i].at - p[i-1].ct);
        }
    }
    
    // calculate turn around time and waiting time
    for(int i=0; i<n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        total_tat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
    }
    
}

void SJF(int n)
{
    int flag;
    
    // sort process according to arrival time
    sort_process_at(n);
    
    // sort process according to burst time
    for(int i=0; i<n; i++)
    {
        if(p[0].at == p[i].at)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    }
    
    if(flag == 1)
    {
        sort_process_bt(0, n);
        p[0].ct = p[0].at + p[0].bt;
    }
    else
    {
        p[0].ct = p[0].at + p[0].bt;
        sort_process_bt(1, n);
    }
    
    
    // calculate completion time
    for(int i=1; i<n; i++)
    {
        p[i].ct = p[i-1].ct + p[i].bt;
        
        // for late arrival process (maintains idol state)
        if(p[i].at > p[i-1].ct)
        {
            p[i].ct += (p[i].at - p[i-1].ct);
        }
    }
    
    // calculate turn around time and waiting time
    for(int i=0; i<n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        total_tat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
    }
    
}

void SRTN(int n)
{
    struct process temp[20];
    int total_time = 0, curr_time;
    
    // sort process according to arrival time    
    sort_process_at(n);   
    
    for(int i=0; i<n; i++)
    {
        temp[i] = p[i];
        temp[i].flag = 0;
        total_time += p[i].bt;
    }
    
    // calculate completion time with pre-emption
    int i=0;
    for(curr_time = 0; curr_time<=total_time; curr_time++)
    {
        if(temp[i].at <= curr_time && temp[i].bt > 0)
        {
            temp[i].bt--;
        }
        
        if(temp[i].bt <=0 && temp[i].flag != 1)
        {
            temp[i].flag = 1;
            p[i].ct = curr_time+1;
        }
        int min = 999;
        for(int j=0; j<n; j++)
        {
            if(temp[j].at <= (curr_time+1) && temp[j].flag != 1) 
            {
                if(min > temp[j].bt)
                {
                    min = temp[j].bt;
                    i = j;
                }
            }
        }
    }
    
    // calculate turn around time and waiting time
    for(int i=0; i<n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        total_tat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
    }
    
}

void sort_process_bt(int s, int n)
{
    struct process temp;
    for(int i=1; i<n; i++)
    {
        for(int j=s; j<n-i; j++)
        {
            if(p[j].bt > p[j+1].bt)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
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