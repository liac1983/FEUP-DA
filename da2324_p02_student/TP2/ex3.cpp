// By: Gonçalo Leão

#include <vector>


using namespace std;

unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // Static memory allocation is used since it's faster but this assumes there are at most 20 items (n <= 20).
    bool curCandidate[20]; // current solution candidate being built
// Prepare the first candidate
    for(unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }
// Iterate over all the candidates
    bool foundSol = false;
    unsigned int maxValue; // value of the best solution found so far
    while (true) {
// Verify if the candidate is a solution
        unsigned int totalValue = 0;
        unsigned int totalWeight = 0;
        for(unsigned int k = 0; k < n; k++) {
            totalValue += values[k]*curCandidate[k];
            totalWeight += weights[k]*curCandidate[k];
        }
        if(totalWeight <= maxWeight) {
// Check if the solution is better than the previous one (or if it's the first one)
            if(!foundSol || totalValue > maxValue) {
                foundSol = true;
                maxValue = totalValue;
                for(unsigned int k = 0; k < n; k++) {
                    usedItems[k] = curCandidate[k];
                }
            }
        }
// Get the next candidate
        unsigned int curIndex = 0;
        while(curCandidate[curIndex]) {
            curIndex++;
            if(curIndex == n) break;
        }
        if(curIndex == n) break;
        for(unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }
    return maxValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}