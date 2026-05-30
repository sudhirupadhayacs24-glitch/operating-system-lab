#include <stdio.h>
#include <limits.h>

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int smallest = INT_MAX;
    int second_smallest = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        }
        else if(arr[i] > smallest && arr[i] < second_smallest) {
            second_smallest = arr[i];
        }
    }

    if(second_smallest == INT_MAX) {
        printf("No second smallest element exists.\n");
    } else {
        printf("Second smallest element = %d\n", second_smallest);
    }

    return 0;
}