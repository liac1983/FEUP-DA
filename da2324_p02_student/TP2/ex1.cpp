// By: Gonçalo Leão
// With contributions by Eduardo Almeida

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = A[0];
    int currentSum;

    for (int start = 0; start < n; start++) {
        currentSum = 0;
        for (int end = start; end < n; end++) {
            currentSum += A[end];
            if (currentSum > maxSum) {
                maxSum = currentSum;
                i = start;
                j = end;
            }
        }
    }

    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}