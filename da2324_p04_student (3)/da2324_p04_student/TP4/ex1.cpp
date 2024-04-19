#include "exercises.h"
#include "cmath"


int maxCrossingSum(int A[], int low, int mid, int high, int &leftIndex, int &rightIndex) {
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            leftIndex = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= high; ++j) {
        sum += A[j];
        if (sum > rightSum) {
            rightSum = sum;
            rightIndex = j;
        }
    }

    return leftSum + rightSum;
}

int maxSubsequenceDC(int A[], int low, int high, int &i, int &j) {
    if (low == high) {
        i = low;
        j = high;
        return A[low];
    }

    int mid = (low + high) / 2;

    int leftI, leftJ, rightI, rightJ, crossI, crossJ;
    int leftSum = maxSubsequenceDC(A, low, mid, leftI, leftJ);
    int rightSum = maxSubsequenceDC(A, mid + 1, high, rightI, rightJ);
    int crossSum = maxCrossingSum(A, low, mid, high, crossI, crossJ);

    if (leftSum >= rightSum && leftSum >= crossSum) {
        i = leftI;
        j = leftJ;
        return leftSum;
    } else if (rightSum >= leftSum && rightSum >= crossSum) {
        i = rightI;
        j = rightJ;
        return rightSum;
    } else {
        i = crossI;
        j = crossJ;
        return crossSum;
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if (n == 0) {
        return 0; // Empty array
    }
    return maxSubsequenceDC(A, 0, n - 1, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}