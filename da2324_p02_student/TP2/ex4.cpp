// By: Gonçalo Leão

#include <algorithm>
#include <vector>

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    // Create a vector of pairs to store the value-to-weight ratios and the corresponding item index
    std::vector<std::pair<double, int>> valueWeightRatio(n);
    for (int i = 0; i < n; ++i) {
        valueWeightRatio[i] = std::make_pair((double) values[i] / weights[i], i);
    }

    // Sort items based on their value-to-weight ratio in non-increasing order
    std::sort(valueWeightRatio.begin(), valueWeightRatio.end(), std::greater<std::pair<double, int>>());

    double totalValue = 0.0;
    // Initialize usedItems array to store the portion of each item used
    std::fill(usedItems, usedItems + n, 0.0);

    // Iterate through the sorted items and add items to the knapsack
    for (int i = 0; i < n; ++i) {
        int index = valueWeightRatio[i].second; // Retrieve the original index of the item
        if (weights[index] <= maxWeight) {
            // If the item can be fully included in the knapsack, include it entirely
            usedItems[index] = 1.0;
            totalValue += values[index];
            maxWeight -= weights[index];
        } else {
            // If the item cannot be fully included, include a fraction of it
            usedItems[index] = (double) maxWeight / weights[index];
            totalValue += usedItems[index] * values[index];
            break; // No need to continue as the knapsack is full
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