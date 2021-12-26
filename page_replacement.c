#include<stdio.h>
#define MAX 30

int fifo(int str[], int f, int p);
int optimal(int str[], int f, int p);
int lru(int str[], int f, int p);

int main()
{
    int choice, f, p, i, str[MAX];
    printf("Enter Choice\n1. FIFO\n2. Optimal\n3. LRU\n   Choose : ");
    scanf("%d", &choice);
    printf("\nEnter Number of Frames : ");
    scanf("%d", &f);
    printf("\nEnter Number of Pages : ");
    scanf("%d", &p);
    printf("\nEnter Page String of %d Size : ", p);
    
    for(i=0; i<p; i++)
    {
        scanf("%d", &str[i]);
    }
    switch(choice)
    {
        case 1:
            printf("FIFO Page Fault: %d",fifo(str, f, p));
            break;
        case 2:
            printf("OPTIMAL Page Fault: %d",optimal(str, f, p));
            break;
        case 3:
            printf("LRU Page Fault: %d",lru(str, f, p));
            break;
    }
}

int fifo(int str[], int f, int p)
{
    int temp[f], i, j, s, page_fault=0;
    for(i=0; i<f; i++)
    {
        temp[i] = -1;
    }
    
    for(i=0; i<p; i++)
    {
        s = 0;
        for(j=0; j<f; j++)
        {
            if(str[i] == temp[j])
            {
                s++;
                page_fault--;
            }
        }
    
    
    page_fault++;
    if((page_fault <= f) && (s==0))
    {
        temp[i] = str[i];
    }
    
    else if(s==0)
    {
        temp[(page_fault - 1) % f] = str[i];
    }
    }
    return page_fault;
}

int optimal(int str[], int f, int p)
{
    int i, j, k, frames[f], page_fault=0, temp[10];
    int flag1, flag2, flag3, max, pos;
    for(i=0; i<f; i++)
    {
        frames[i] = -1;
    }
    
    for(i=0; i<p; i++)
    {
        flag1 = flag2 = 0;
        for(j=0; j<f; j++)
        {
            if(frames[j] == str[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }
        
        if(flag1 == 0)
        {
            for(j=0; j<f; j++)
            {
                if(frames[j] == -1)
                {
                    page_fault++;
                    frames[j] = str[i];
                    flag2 = 1;
                    break;
                }
            }
        }
        
        if(flag2 == 0)
        {
            flag3 = 0;
            for(j=0; j<f; j++)
            {
                temp[j] = -1;
            
                for(k=i+1; k<p; k++)
                {
                    if(frames[j] == str[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            
            for(j=0; j<f; j++)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            
            if(flag3 == 0)
            {
                max = temp[0];
                pos = 0;
                
                for(j=1; j<f; j++)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            
            frames[pos] = str[i];
            page_fault++;
        }
    }
    return page_fault;
}


int lru(int str[], int f, int p)
{
    int frame[f], count[10]={0};
    int i, j, page_fault=0, pos=0, repindex, leastcount, flag;
    for(i=0; i<f; i++)
    {
        frame[i] = -1;
    }
    for(i=0; i<p; i++)
    {
        flag = 0;
        for(j=0; j<f; j++)
        {
            if(str[i]==frame[j])
            {
                flag = 1;
                count[j]++;
                break;
            }
        }
        
        if(flag==0 && page_fault<f)
        {
            frame[pos] = str[i];
            count[pos] = 1;
            pos = (pos+1)%f;
            page_fault++;
        }
        else if(flag==0)
        {
            repindex=0;
            leastcount = count[0];
            for(j=1;j<f;j++)
            {
                if(count[j]<leastcount)
                {
                    repindex = j;
                    leastcount=count[j];
                }
            }
            
            frame[repindex] = str[i];
            count[repindex] = 1;
            page_fault++;
        }
    }
    
    return page_fault;
}
