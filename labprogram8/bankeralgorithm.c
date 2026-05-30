#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m], work[m];
    bool finish[n];
    int safeSeq[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation: ");
        for (int j = 0; j < m; j++) scanf("%d", &alloc[i][j]);
        printf("Enter Max: ");
        for (int j = 0; j < m; j++) scanf("%d", &max[i][j]);
        finish[i] = false;
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break; // Exit loop if no more processes can be finished
    }

    if (count == n) {
        printf("\nSYSTEM IS IN SAFE STATE\nSafe Sequence: <");
        for (int i = 0; i < n; i++) printf(" P%d%s", safeSeq[i], (i == n - 1) ? "" : ",");
        printf(" >\n");
    } else {
        printf("\nSYSTEM IS IN UNSAFE STATE (DEADLOCK DETECTED)\n");
        printf("Deadlocked processes are: ");
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}