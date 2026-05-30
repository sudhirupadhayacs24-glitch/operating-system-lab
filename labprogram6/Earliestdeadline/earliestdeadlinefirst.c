#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int C;          // Capacity (execution time)
    int T;          // Period
    int D;          // Relative deadline
    int remaining;  // Remaining execution time
    int release;    // Next release time
    int absDeadline;// Absolute deadline of current job
} Task;

// GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    Task tasks[MAX];
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int hyperPeriod = 1;
    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);
        tasks[i].id = i + 1;

        printf("Capacity (C): ");
        scanf("%d", &tasks[i].C);

        printf("Period (T): ");
        scanf("%d", &tasks[i].T);

        printf("Deadline (D): ");
        scanf("%d", &tasks[i].D);

        tasks[i].remaining = 0;
        tasks[i].release = 0;
        tasks[i].absDeadline = 0;

        if (i == 0) hyperPeriod = tasks[i].T;
        else hyperPeriod = lcm(hyperPeriod, tasks[i].T);
    }

    printf("\n--- EDF Scheduling Simulation up to Hyperperiod = %d ---\n", hyperPeriod);

    for (int time = 0; time < hyperPeriod; time++) {
        // Release jobs at their period
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].release) {
                tasks[i].remaining = tasks[i].C;
                tasks[i].absDeadline = time + tasks[i].D;
                tasks[i].release += tasks[i].T;
            }
        }

        // Select ready job with earliest deadline
        int idx = -1, minDeadline = 1e9;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                if (tasks[i].absDeadline < minDeadline) {
                    minDeadline = tasks[i].absDeadline;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("P%d ", tasks[idx].id);
            tasks[idx].remaining--;
        } else {
            printf("Idle ");
        }
    }

    printf("\n");
    return 0;
}