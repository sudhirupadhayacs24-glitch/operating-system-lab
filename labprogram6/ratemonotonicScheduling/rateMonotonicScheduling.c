#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id, burst, period;
    int remaining, next_arrival;
} Task;

int main() {
    Task t[MAX];
    int n, time, hyper = 20;
    float U = 0;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);
        t[i].id = i + 1;

        printf("Execution Time: ");
        scanf("%d", &t[i].burst);

        printf("Period: ");
        scanf("%d", &t[i].period);

        t[i].remaining = 0;
        t[i].next_arrival = 0;

        U += (float)t[i].burst / t[i].period;
    }

    float bound = n * (pow(2, (float)1/n) - 1);

    printf("\nUtilization = %.2f\n", U);
    printf("Bound = %.2f\n", bound);

    if (U <= bound)
        printf("Schedulable\n");
    else
        printf("Not guaranteed schedulable\n");

    printf("\nTimeline:\n");

    for (time = 0; time < hyper; time++) {

        for (int i = 0; i < n; i++) {
            if (time == t[i].next_arrival) {
                t[i].remaining = t[i].burst;
                t[i].next_arrival += t[i].period;
            }
        }

        int idx = -1, minp = 1e9;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0 && t[i].period < minp) {
                minp = t[i].period;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("T%d ", t[idx].id);
            t[idx].remaining--;
        } else {
            printf("Idle ");
        }
    }

    return 0;
}