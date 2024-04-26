// By: Gonçalo Leão

#include "exercises.h"

static void backtrack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[], unsigned int currVal, unsigned int currWeight, unsigned int index, unsigned int &maxVal, std::vector<bool> &includedItems) {
    if (index == n) {
        if (currVal > maxVal) {
            maxVal = currVal;
            for (unsigned int i = 0; i < n; ++i) {
                usedItems[i] = includedItems[i];
            }
        }
        return;
    }

    if (weights[index] <= maxWeight - currWeight) {
        includedItems[index] = true;
        backtrack(values, weights, n, maxWeight, usedItems, currVal + values[index], currWeight + weights[index], index + 1, maxVal, includedItems);
        includedItems[index] = false;
    }
    backtrack(values, weights, n, maxWeight, usedItems, currVal, currWeight, index + 1, maxVal, includedItems);
}

unsigned int knapsackBT(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxVal = 0;
    std::vector<bool> includedItems(n, false);
    backtrack(values, weights, n, maxWeight, usedItems, 0, 0, 0, maxVal, includedItems);
    return maxVal;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex1, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP7_Ex1, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}