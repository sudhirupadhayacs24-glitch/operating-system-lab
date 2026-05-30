#include <stdio.h>
#include <stdlib.h>

int chopstick[5] = {1, 1, 1, 1, 1};
int room = 4;
int phil_pos[5];

void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void philosopher(int i) {
    printf("P %d is waiting\n", i + 1);
    wait(&room);
    wait(&chopstick[i]);
    wait(&chopstick[(i + 1) % 5]);
    printf("P %d is granted to eat\n", i + 1);
    printf("P %d has finished eating\n", i + 1);
    signal(&chopstick[i]);
    signal(&chopstick[(i + 1) % 5]);
    signal(&room);
}

int main() {
    int total, hungry, choice, i;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);
    printf("How many are hungry: ");
    scanf("%d", &hungry);

    for (i = 0; i < hungry; i++) {
        printf("Enter philosopher %d position (1 to 5): ", i + 1);
        scanf("%d", &phil_pos[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            for (i = 0; i < hungry; i++) {
                philosopher(phil_pos[i] - 1);
            }
        } else if (choice == 3) {
            exit(0);
        }
    }
    return 0;
}