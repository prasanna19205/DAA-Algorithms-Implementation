#include <stdio.h>
#include <math.h>

// Structure for a point
typedef struct {
    int x, y;
} Point;

// Function to calculate distance
float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

// Function to find closest pairs
void closestPair(Point P[], int n) {
    float min = 999999;

    // Step 1: Find minimum distance
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float d = distance(P[i], P[j]);
            if (d < min) {
                min = d;
            }
        }
    }

    // Step 2: Print all pairs with that minimum distance
    printf("Minimum Distance: %.2f\n", min);
    printf("Closest Pairs:\n");

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float d = distance(P[i], P[j]);

            // Compare with small tolerance for float precision
            if (fabs(d - min) < 0.0001) {
                printf("(%d,%d) and (%d,%d)\n",
                       P[i].x, P[i].y,
                       P[j].x, P[j].y);
            }
        }
    }
}

int main() {
    // Your test input
    Point P[] = {{12,13}, {1,1}, {2,2}, {4,6}, {4,5}, {2,4}};
    int n = sizeof(P)/sizeof(P[0]);

    closestPair(P, n);

    return 0;
}