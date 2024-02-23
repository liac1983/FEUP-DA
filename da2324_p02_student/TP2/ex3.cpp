// By: Gonçalo Leão

#include <vector>


using namespace std;

unsigned int calculateTotalValue(const std::vector<unsigned int>& values, const std::vector<unsigned int>& weights, const std::vector<bool>& chosenItems) {
    unsigned int totalValue = 0;
    for (size_t i = 0; i < values.size(); ++i) {
        if (chosenItems[i]) {
            totalValue += values[i];
        }
    }
    return totalValue;
}
void knapsackBruteForce(const std::vector<unsigned int>& values, const std::vector<unsigned int>& weights, size_t index, unsigned int maxWeight, std::vector<bool>& chosenItems, std::vector<bool>& bestChosenItems, unsigned int& bestValue) {
    if (index == values.size()) {
        unsigned int totalWeight = 0;
        for (size_t i = 0; i < values.size(); ++i) {
            if (chosenItems[i]) {
                totalWeight += weights[i];
            }
        }
        if (totalWeight <= maxWeight) {
            unsigned int totalValue = calculateTotalValue(values, weights, chosenItems);
            if (totalValue > bestValue) {
                bestValue = totalValue;
                bestChosenItems = chosenItems;
            }
        }
        return;
    }
    chosenItems[index] = true;
    knapsackBruteForce(values, weights, index + 1, maxWeight, chosenItems, bestChosenItems, bestValue);
    chosenItems[index] = false;
    knapsackBruteForce(values, weights, index + 1, maxWeight, chosenItems, bestChosenItems, bestValue);
}


unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    std::vector<unsigned int> valuesVec(values, values + n);
    std::vector<unsigned int> weightsVec(weights, weights + n);
    std::vector<bool> chosenItems(n, false);
    std::vector<bool> bestChosenItems;
    unsigned int bestValue = 0;
    knapsackBruteForce(valuesVec, weightsVec, 0, maxWeight, chosenItems, bestChosenItems, bestValue);
    for (size_t i = 0; i < n; ++i) {
        usedItems[i] = bestChosenItems[i];
    }
    return bestValue;
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