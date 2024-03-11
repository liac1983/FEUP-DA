// By: Gonçalo Leão

#include <algorithm>
#include <vector>

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    // Step 1: Sort items by decreasing value/weight ratio
    std::vector<unsigned int> sortedIndices;
    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = 0.0;
        sortedIndices.push_back(i);
    }
    std::sort(sortedIndices.begin(), sortedIndices.end(), [values,weights](unsigned int i,
                                                                           unsigned int j) {
        return static_cast<double>(values[i])/weights[i] >
               static_cast<double>(values[j])/weights[j];
    });
// Step 2: Process the items
    double totalValue = 0.0;
    unsigned int remaningWeight = maxWeight;
    for(unsigned int i = 0; i < n; i++) {
        if(remaningWeight == 0) break; // stop earlier because the knapsack is full
        if(remaningWeight >= weights[sortedIndices[i]]) {
// Fully add the next item
            usedItems[sortedIndices[i]] = 1.0;
            totalValue += static_cast<double>(values[sortedIndices[i]]);
            remaningWeight -= weights[sortedIndices[i]];
        }
        else {
// Partially add the item to completely fill the knapsack
            usedItems[sortedIndices[i]] = static_cast<double>(remaningWeight) /
                                          weights[sortedIndices[i]];
            totalValue += usedItems[sortedIndices[i]] * values[sortedIndices[i]];
            break;
        }
    }
    return totalValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}