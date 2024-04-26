// By: Gonçalo Leão

#include "exercises.h"

bool subsetSumBT(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    if (n == 0) {
        return (T == 0 && subsetSize > 0); // Check if the desired sum is reached and subset is not empty
    }
    if (T < 0) {
        return false; // No subset with sum equal to target sum found
    }

    // Exclude the last element and recursively search
    if (subsetSumBT(A, n - 1, T, subset, subsetSize)) {
        return true;
    }

    // Include the last element if there is enough space in subset array
    if (subsetSize < n) {
        subset[subsetSize++] = A[n - 1];
        if (subsetSumBT(A, n - 1, T - A[n - 1], subset, subsetSize)) {
            return true;
        }
        // Backtrack if including the last element didn't lead to the target sum
        subsetSize--;
    }

    return false;
}




/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP7_Ex5, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;

    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), false);
}