#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0, pos;
    int at[10], bt[10], pr[10], rt[10];
    int ct[10], tat[10], wt[10];
    int min;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i+1);
        scanf("%d", &at[i]);

        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &bt[i]);

        printf("Process %d Priority: ", i+1);
        scanf("%d", &pr[i]);

        rt[i] = bt[i];
    }

    while(completed < n) {
        min = 999;
        pos = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && pr[i] < min) {
                min = pr[i];
                pos = i;
            }
        }

        if(pos == -1) {
            time++;
        } else {
            rt[pos]--;
            time++;

            if(rt[pos] == 0) {
                completed++;
                ct[pos] = time;
                tat[pos] = ct[pos] - at[pos];
                wt[pos] = tat[pos] - bt[pos];
            }
        }
    }

    printf("\nPID\tAT\tBT\tPR\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], pr[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}