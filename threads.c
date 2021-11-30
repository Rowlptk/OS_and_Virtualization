#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

# define MAX 10

void *mult(void* arg);


int main()
{
    int m1[MAX][MAX], m2[MAX][MAX];
    int r1, c1, r2, c2;
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    
    
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c1; j++)
        {
            scanf("%d", &m1[i][j]);
        }
    }
    
    for(int i=0; i<r2; i++)
    {
        for(int j=0; j<c2; j++)
        {
            scanf("%d", &m2[i][j]);
        }
    }
   
    int max = r1*c2;
    
    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));
    
    int count = 0;
    int *data = NULL;
    
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c2; j++)
        {
            data = (int*)malloc((20)*sizeof(int));
            data[0] = c1;
    
            for(int k=0; k<c1; k++)
            {
                data[k+1] = m1[i][k];
            }
            
            for(int k=0; k<r2; k++)
            {
                data[k+c1+1] = m2[k][j];
            }
            
            
            pthread_create(&threads[count++], NULL, mult, (void*)(data));
    
        }
    }
    
    for(int i=0; i<max; i++)
    {
        void *k;
        
        pthread_join(threads[i], &k);
        
        int *p = (int*)k;
        printf("%d ", *p);
    }
    
    
    return 0;
}


void *mult(void* arg)
{
    int *data = (int*)arg;
    int k=0, i=0;
    
    int x = data[0];
    for(i=1; i<=x; i++)
    {
        k += data[i]*data[i+x];
    }
    
    int *p = (int*)malloc(sizeof(int));
        *p = k;
    pthread_exit(p);
}

