#include <stdio.h>
#include <string.h>

// Function to find minimum of 3 numbers
int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    else if (b <= c) return b;
    else return c;
}

void editDistance(char X[], char Y[]) {
    int n = strlen(X);
    int m = strlen(Y);

    int dp[n+1][m+1];

    // Step 1: Fill DP table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {

            if (i == 0)
                dp[i][j] = j; // insert all
            else if (j == 0)
                dp[i][j] = i; // delete all
            else if (X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(
                    dp[i-1][j],    // delete
                    dp[i][j-1],    // insert
                    dp[i-1][j-1]   // replace
                );
        }
    }

    // Step 2: Print minimum operations
    printf("Minimum Edit Distance: %d\n", dp[n][m]);

    // Step 3: Backtrack to print operations
    int i = n, j = m;

    printf("Operations:\n");

    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            i--; j--;
        }
        else if (dp[i][j] == dp[i-1][j-1] + 1) {
            printf("Replace %c with %c\n", X[i-1], Y[j-1]);
            i--; j--;
        }
        else if (dp[i][j] == dp[i-1][j] + 1) {
            printf("Delete %c\n", X[i-1]);
            i--;
        }
        else {
            printf("Insert %c\n", Y[j-1]);
            j--;
        }
    }

    while (i > 0) {
        printf("Delete %c\n", X[i-1]);
        i--;
    }

    while (j > 0) {
        printf("Insert %c\n", Y[j-1]);
        j--;
    }
}

int main() {
    char X[] = "cat";
    char Y[] = "cut";

    editDistance(X, Y);

    return 0;
