#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;

void wait_m() {
    --mutex;
}

void signal_m() {
    ++mutex;
}

void producer() {
    if (empty != 0) {
        wait_m();
        ++full;
        --empty;
        x++;
        printf("Producer has produced: Item %d\n", x);
        signal_m();
    } else {
        printf("Buffer is full!\n");
    }
}

void consumer() {
    if (full != 0) {
        wait_m();
        --full;
        ++empty;
        printf("Consumer has consumed: Item %d\n", x);
        x--;
        signal_m();
    } else {
        printf("Buffer is empty!\n");
    }
}

int main() {
    int n;
    while (1) {
        printf("\n1. Producer\n2. Consumer\n3. Exit\nEnter choice: ");
        scanf("%d", &n);
        switch (n) {
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: exit(0);
        }
    }
    return 0;
}