#include <stdio.h>

struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int type; // 0 = System, 1 = User
};

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], temp;

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Type (0=System, 1=User): ");
        scanf("%d", &p[i].type);
    }

    // Sort by type, then arrival time
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(p[i].type > p[j].type ||
              (p[i].type == p[j].type && p[i].at > p[j].at)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    float total_tat = 0, total_wt = 0;

    // Execution (FCFS)
    for(i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    // Output
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].type,
            p[i].ct, p[i].tat, p[i].wt);
    }

    // Average calculations
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}