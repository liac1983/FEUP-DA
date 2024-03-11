// By: Gonçalo Leão
#include <iostream>
#include <vector>
#include <algorithm>

// Bruteforce
bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // Static memory allocation is used since it's faster but this assumes there are at most 20 coin values (n <= 20).
    unsigned int curCandidate[20]; // current solution candidate being built
// Prepare the first candidate
    for(unsigned int i = 0; i < n; i++) {
        curCandidate[i] = 0;
    }
// Iterate over all the candidates
    bool foundSol = false;
    unsigned int minCoins; // value of the best solution found so far
    while (true) {
// Verify if the candidate is a solution
        unsigned int totalValue = 0;
        unsigned int totalCoins = 0;
        for(unsigned int k = 0; k < n; k++) {
            totalValue += C[k]*curCandidate[k];
            totalCoins += curCandidate[k];
        }
        if(totalValue == T) {
// Check if the solution is better than the previous one (or if it's the first one)
            if(!foundSol || totalCoins < minCoins) {
                foundSol = true;
                minCoins = totalCoins;
                for(unsigned int k = 0; k < n; k++) {
                    usedCoins[k] = curCandidate[k];
                }
            }
        }
// Get the next candidate
        unsigned int curIndex = 0;
        while(curCandidate[curIndex] == Stock[curIndex]) {
            curIndex++;
            if(curIndex == n) break;
        }
        if(curIndex == n) break;
// Set the stock of the higher coin values in the candidate solution back to 0.
// Example with 1 stock per coin value: 1 1 0 1 -> 0 0 1 1.
// Enumeration of the 8 candidates for 3 coin values with 0-1 stock:
// 0 0 0 -> 1 0 0 -> 0 1 0 -> 1 1 0 -> 0 0 1 -> 1 0 1 -> 0 1 1 -> 1 1 1
// (it's like incrementing by 1 numbers in binary written backwards)
        for(unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = 0;
        }
        curCandidate[curIndex]++;
    }
    return foundSol;
}

// Greedy
// Time: O(D*S), Space: O(D), where D is the number of coin values and S is the maximum amount of stock of any value
bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for(unsigned int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }
    for(int i = n - 1; i >= 0; i--) {
        while(usedCoins[i] < Stock[i] && T >= C[i]) {
            usedCoins[i]++;
            T -= C[i];
        }
    }
    return T == 0;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}

TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}