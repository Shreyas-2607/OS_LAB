#include <stdio.h>

#define MAX 100

int isHit(int frame[], int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frame[i] == page)
            return 1;
    }
    return 0;
}

void printFrames(int frame[], int f) {
    for (int i = 0; i < f; i++) {
        if (frame[i] != -1)
            printf("%d ", frame[i]);
        else
            printf("- ");
    }
    printf("\n");
}


void FIFO(int pages[], int n, int f) {
    int frame[MAX], index = 0, pageFaults = 0;
    for (int i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        if (!isHit(frame, pages[i], f)) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }
        printFrames(frame, f);
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}


void LRU(int pages[], int n, int f) {
    int frame[MAX], time[MAX], pageFaults = 0;
    for (int i = 0; i < f; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int flag = 0;

        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                time[j] = i + 1;
                break;
            }
        }

        if (!flag) {
            int minTime = time[0], pos = 0;
            for (int j = 1; j < f; j++) {
                if (time[j] < minTime) {
                    minTime = time[j];
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            time[pos] = i + 1;
            pageFaults++;
        }

        printFrames(frame, f);
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}


void Optimal(int pages[], int n, int f) {
    int frame[MAX], pageFaults = 0;
    for (int i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        if (!isHit(frame, pages[i], f)) {
            int found = 0;
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    found = 1;
                    break;
                }
            }

            if (!found) {
                int farthest = -1, pos = -1;
                for (int j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
                frame[pos] = pages[i];
            }

            pageFaults++;
        }

        printFrames(frame, f);
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}


int main() {
    int pages[MAX], n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\nChoose Algorithm:\n");
    printf("1. FIFO\n2. LRU\n3. Optimal\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: FIFO(pages, n, f); break;
        case 2: LRU(pages, n, f); break;
        case 3: Optimal(pages, n, f); break;
        default: printf("Invalid Choice!\n");
    }

    return 0;
}