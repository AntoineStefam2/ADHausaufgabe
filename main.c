#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to find the minimum of three integers
int min(int x, int y, int z) {
    if (x <= y && x <= z)
        return x;
    else if (y <= x && y <= z)
        return y;
    else
        return z;
}

// Function to compute the minimum edit distance between two strings
int minDis(char* s1, char* s2, int a, int b) {
    int *dp1 = (int *)malloc((m + 1) * sizeof(int));
    int *dp2 = (int *)malloc((m + 1) * sizeof(int));

    // Check if memory allocation was successful
    if (!dp1 || !dp2) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Initialize the first row (base case for empty s1)
    for (int j = 0; j <= m; j++)
        dp1[j] = j;

    // Iterate over each character of s1
    for (int i = 1; i <= n; i++) {
        // Initialize the first column (base case for empty s2)
        dp2[0] = i;

        // Iterate over each character of s2
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                // If characters match, no operation needed
                dp2[j] = dp1[j - 1];
            else
                // If characters don't match, consider all operations and take the minimum
                dp2[j] = 1 + min(dp2[j - 1], dp1[j], dp1[j - 1]);
        }

        // Copy dp2 to dp1 for the next iteration
        for (int j = 0; j <= m; j++)
            dp1[j] = dp2[j];
    }

    // Result is the edit distance for transforming s1 to s2
    int result = dp1[m];

    free(dp1);
    free(dp2);

    return result;
}

// Function to generate a random string of a given length
void generateRandomString(char* str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++) {
        // Select a random character from the charset
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    // Null-terminate the string
    str[length] = '\0';
}

int main() {

    srand(time(NULL));
    int a = 100000;
    int b = 500000;
    char* s1 = (char *)malloc((a + 1) * sizeof(char));
    char* s2 = (char *)malloc((b + 1) * sizeof(char));

    if (!s1 || !s2) {
        printf("Memory allocation failed\n");
        return 1;
    }
    generateRandomString(s1, a);
    generateRandomString(s2, b);
    printf("String 1: %s\n", s1);
    printf("String 2: %s\n", s2);
    printf("Minimum edit distance: %d\n", minDis(s1, s2, a, b));
    free(s1);
    free(s2);
    return 0;
}
