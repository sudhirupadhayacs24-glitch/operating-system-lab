#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_REF 100

// Helper function to print the current state of frames
void printFrames(int pfCount, int frames[], int numFrames) {
    printf("PF No. %d: ", pfCount);
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

// 1. First In First Out (FIFO)
void simulateFIFO(int refStr[], int refLen, int numFrames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < numFrames; i++) frames[i] = -1;

    int pfCount = 0;
    int insertIndex = 0;

    printf("FIFO Page Replacement Process:\n");

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];
        bool isHit = false;

        // Check for page hit
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                isHit = true;
                break;
            }
        }

        // Page Fault occurs
        if (!isHit) {
            pfCount++;
            frames[insertIndex] = page;
            insertIndex = (insertIndex + 1) % numFrames; // Circular queue logic
            printFrames(pfCount, frames, numFrames);
        }
    }
    printf("FIFO Page Faults: %d\n\n", pfCount);
}

// 2. Least Recently Used (LRU)
void simulateLRU(int refStr[], int refLen, int numFrames) {
    int frames[MAX_FRAMES];
    int timeRecent[MAX_FRAMES]; // Tracks when each frame slot was last used
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        timeRecent[i] = -1;
    }

    int pfCount = 0;

    printf("LRU Page Replacement Process:\n");

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];
        bool isHit = false;
        int hitIndex = -1;

        // Check for page hit
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                isHit = true;
                hitIndex = j;
                break;
            }
        }

        if (isHit) {
            // Update the last used time for this hit frame
            timeRecent[hitIndex] = i;
        } else {
            pfCount++;
            int replaceIndex = -1;

            // Check for empty slots first
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty slot, find the least recently used one
            if (replaceIndex == -1) {
                int minTime = timeRecent[0];
                replaceIndex = 0;
                for (int j = 1; j < numFrames; j++) {
                    if (timeRecent[j] < minTime) {
                        minTime = timeRecent[j];
                        replaceIndex = j;
                    }
                }
            }

            frames[replaceIndex] = page;
            timeRecent[replaceIndex] = i;
            printFrames(pfCount, frames, numFrames);
        }
    }
    printf("LRU Page Faults: %d\n\n", pfCount);
}

// 3. Optimal Page Replacement
void simulateOptimal(int refStr[], int refLen, int numFrames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < numFrames; i++) frames[i] = -1;

    int pfCount = 0;

    printf("Optimal Page Replacement Process:\n");

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];
        bool isHit = false;

        // Check for page hit
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                isHit = true;
                break;
            }
        }

        if (!isHit) {
            pfCount++;
            int replaceIndex = -1;

            // Check for empty slots first
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty slot, look into the future reference string
            if (replaceIndex == -1) {
                int farthest = i;
                for (int j = 0; j < numFrames; j++) {
                    int k;
                    for (k = i + 1; k < refLen; k++) {
                        if (frames[j] == refStr[k]) {
                            break;
                        }
                    }
                    // If a page is not needed in the future at all, choose it immediately
                    if (k == refLen) {
                        replaceIndex = j;
                        break;
                    }
                    // Otherwise, pick the one needed farthest in the future
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }
            }

            frames[replaceIndex] = page;
            printFrames(pfCount, frames, numFrames);
        }
    }
    printf("Optimal Page Faults: %d\n\n", pfCount);
}

int main() {
    int numFrames;
    int refLen;
    int refStr[MAX_REF];

    // Read Inputs exactly matching the requested execution output
    printf("Enter the number of Frames: ");
    scanf("%d", &numFrames);

    printf("Enter the length of reference string: ");
    scanf("%d", &refLen);

    printf("Enter the reference string: ");
    for (int i = 0; i < refLen; i++) {
        scanf("%d", &refStr[i]);
    }

    // Run the simulations
    simulateFIFO(refStr, refLen, numFrames);
    simulateLRU(refStr, refLen, numFrames);
    simulateOptimal(refStr, refLen, numFrames);

    return 0;
}