#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure for a point
typedef struct {
    int x, y;
} Point;

// Compare points by x-coordinate
int compareX(const void *a, const void *b) {
    return ((Point*)a)->x - ((Point*)b)->x;
}

// Compare points by y-coordinate
int compareY(const void *a, const void *b) {
    return ((Point*)a)->y - ((Point*)b)->y;
}

// Distance between two points
float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

// Brute force method for small number of points
float bruteForce(Point P[], int n) {
    float min = 999999;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float d = distance(P[i], P[j]);
            if (d < min)
                min = d;
        }
    }
    return min;
}

// Find closest distance in strip
float stripClosest(Point strip[], int size, float d) {
    float min = d;

    // Sort strip by y-coordinate
    qsort(strip, size, sizeof(Point), compareY);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size &&
             (strip[j].y - strip[i].y) < min; j++) {

            float dist_val = distance(strip[i], strip[j]);

            if (dist_val < min)
                min = dist_val;
        }
    }
    return min;
}

// Recursive function
float closestUtil(Point P[], int n) {

    // Base case
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    // Divide
    float dl = closestUtil(P, mid);
    float dr = closestUtil(P + mid, n - mid);

    // Minimum distance
    float d = fmin(dl, dr);

    // Build strip
    Point strip[n];
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (abs(P[i].x - midPoint.x) < d) {
            strip[j] = P[i];
            j++;
        }
    }

    // Final result
    return fmin(d, stripClosest(strip, j, d));
}

// Main function
float closest(Point P[], int n) {
    qsort(P, n, sizeof(Point), compareX);
    return closestUtil(P, n);
}

// Driver code
int main() {
    Point P[] = {{2,3}, {12,30}, {40,50}, {5,1}, {12,10}, {3,4}};
    int n = sizeof(P) / sizeof(P[0]);

    printf("Minimum Distance: %.2f\n", closest(P, n));

    return 0;
}