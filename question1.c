#include <stdio.h>
#include <stdlib.h>

// Structure for activity
typedef struct {
    int start, finish;
} Activity;

// Comparator for sorting by finish time
int compare(const void *a, const void *b) {
    Activity *act1 = (Activity *)a;
    Activity *act2 = (Activity *)b;
    return act1->finish - act2->finish;
}

// Function to validate activities
int isValid(Activity a) {
    return a.start < a.finish;
}

// Activity Selection Function
void activitySelection(Activity arr[], int n) {

    // Step 1: Remove invalid activities
    Activity valid[n];
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (isValid(arr[i])) {
            valid[k++] = arr[i];
        } else {
            printf("Skipping invalid activity (%d, %d)\n", arr[i].start, arr[i].finish);
        }
    }

    if (k == 0) {
        printf("No valid activities.\n");
        return;
    }

    // Step 2: Sort valid activities by finish time
    qsort(valid, k, sizeof(Activity), compare);

    printf("\nSelected Activities:\n");

    // Step 3: Select first activity
    int i = 0;
    printf("(%d, %d)\n", valid[i].start, valid[i].finish);

    // Step 4: Select remaining activities
    for (int j = 1; j < k; j++) {
        if (valid[j].start >= valid[i].finish) {
            printf("(%d, %d)\n", valid[j].start, valid[j].finish);
            i = j;
        }
    }
}

int main() {
    // You can change input here
    Activity arr[] = {{2,1}, {0,1}, {1,5}, {4,6}, {1,1}};
    int n = sizeof(arr)/sizeof(arr[0]);

    activitySelection(arr, n);

    return 0;
}