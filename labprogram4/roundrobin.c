#include<stdio.h>

int main()
{
    int n, tq;
    int at[10], bt[10], rt[10];
    int ct[10], tat[10], wt[10];

    int queue[100], front = 0, rear = 0;
    int visited[10] = {0};

    int time = 0, remain, i;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter the number of processes.\n");
    scanf("%d",&n);
    remain = n;

    printf("Enter Arrival Time and Burst Time.\n");
    for(i=0;i<n;i++)
    {
        printf("Process %d AT and BT:",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter the quantum time:");
    scanf("%d",&tq);

    for(i=0;i<n;i++)
    {
        if(at[i] <= time && visited[i] == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(remain != 0)
    {

        if(front == rear)
        {
            time++;
            for(i=0;i<n;i++)
            {
                if(at[i] <= time && visited[i] == 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if(rt[i] > tq)
        {
            time += tq;
            rt[i] -= tq;
        }
        else
        {
            time += rt[i];
            ct[i] = time;
            rt[i] = 0;
            remain--;
        }

        for(int j=0;j<n;j++)
        {
            if(at[j] <= time && visited[j] == 0)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt[i] > 0)
        {
            queue[rear++] = i;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0; i<n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f", avg_wt/n);

    return 0;
}