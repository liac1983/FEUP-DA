// By: Gonçalo Leão

bool subsetSum(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    // Static memory allocation is used since it's faster but this assumes there are at most 20 values in the subset (n <= 100).
    bool curCandidate[20]; // current solution candidate being built
// Prepare the first candidate
    for(unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }
// Iterate over all the candidates
    while (true) {
// Verify if the candidate is a solution
        unsigned int sum = 0;
        for(unsigned int k = 0; k < n; k++) {
            sum += A[k]*((unsigned int)curCandidate[k]);
        }
        if(sum == T) {
// Build and return the solution
            subsetSize = 0;
            for(unsigned int k = 0; k < n; k++) {
                if(curCandidate[k]) {
                    subset[subsetSize++] = A[k];
                }
            }
            return true;
        }
// Get the next candidate
        unsigned int curIndex = 0;
        while(curCandidate[curIndex]) {
            curIndex++;
            if(curIndex == n) break;
        }
        if(curIndex == n) break;
// Set the boolean of the higher positions in A in the candidate solution back to 0.
// Example: 1 1 0 1 -> 0 0 1 1.
// Enumeration of the 8 candidates for an array of length 3:
// 0 0 0 -> 1 0 0 -> 0 1 0 -> 1 1 0 -> 0 0 1 -> 1 0 1 -> 0 1 1 -> 1 1 1
// (it's like incrementing by 1 numbers in binary written backwards)
        for(unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
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

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), false);
}