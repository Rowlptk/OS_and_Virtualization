#include<stdio.h>

struct process{
    int at;     // arrival time
    int bt;     // burst time
    int p;      // priorities
    int ct;     // completion time
    int tat;    // turn around time
    int wt;     // waiting time
    int flag;
}p[10];

void priority_np(int n);
void sort_process_at(int n);
void sort_process_p(int start, int end);
void priority_p(int n);

float total_tat = 0;
float total_wt = 0;

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
        scanf("%d", &p[i].p);
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
    }
    switch(choice)
    {
        case 1:
            priority_np(n);
            break;
        case 2:
            priority_p(n);
            break;
        default:
            printf("\nInvalid Choice!\n");
    }
    
    printf("%.2f %.2f", total_wt/n, total_tat/n);

    return 0;
}

void priority_np(int n)
{
    int curr_time = 0, end;
    // sort process according to arrival time
    sort_process_at(n);
    
    p[0].ct = p[0].at + p[0].bt;
    curr_time = p[0].ct;
    
    // calculate completion time
    for(int i=1; i<n; i++)
    {
        end = i;
        for(int j=i; j<n; j++)
        {
            if(p[j].at<= curr_time)
            {
                end++;
            }
        }
        
        
        // sort process according to priorities
        sort_process_p(i, end);
        
        p[i].ct = p[i-1].ct + p[i].bt;
    
        curr_time = p[i].ct;    
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

void priority_p(int n)
{
    struct process temp[10];
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
    for(curr_time=0; curr_time<=total_time; curr_time++)
    {
        if(temp[i].at <= curr_time && temp[i].bt > 0)
        {
            temp[i].bt--;
        }
        
        if(temp[i].bt <= 0 && temp[i].flag != 1)
        {
            temp[i].flag = 1;
            p[i].ct = curr_time+1;
        }
        int min = 999;
        for(int j=0; j<n; j++)
        {
            if(temp[j].at <= (curr_time+1) && temp[j].flag != 1)
            {
                if(min > temp[j].p)
                {
                    min = temp[j].p;
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


void sort_process_p(int start, int end)
{
    struct process temp;
    for(int i=1; i<end; i++)
    {
        for(int j=start; j<end-i; j++)
        {
            if(p[j].p > p[j+1].p)
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