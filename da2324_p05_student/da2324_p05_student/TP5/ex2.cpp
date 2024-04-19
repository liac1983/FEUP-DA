#include "exercises.h"

unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // Inicialize a matriz de memoização para armazenar os valores ótimos
    unsigned int dp[n + 1][maxWeight + 1];

    // Inicialize a matriz de rastreamento para rastrear os itens selecionados
    bool trace[n + 1][maxWeight + 1];

    // Preencha a tabela de programação dinâmica
    for (unsigned int i = 0; i <= n; ++i) {
        for (unsigned int w = 0; w <= maxWeight; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
                trace[i][w] = false;
            } else if (weights[i - 1] <= w) {
                unsigned int include = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                unsigned int exclude = dp[i - 1][w];
                if (include > exclude) {
                    dp[i][w] = include;
                    trace[i][w] = true;
                } else {
                    dp[i][w] = exclude;
                    trace[i][w] = false;
                }
            } else {
                dp[i][w] = dp[i - 1][w];
                trace[i][w] = false;
            }
        }
    }

    // Reconstrua a solução para determinar quais itens foram selecionados
    unsigned int remainingWeight = maxWeight;
    for (int i = n; i > 0; --i) {
        if (trace[i][remainingWeight]) {
            usedItems[i - 1] = true;
            remainingWeight -= weights[i - 1];
        } else {
            usedItems[i - 1] = false;
        }
    }

    // Retorna o valor máximo que pode ser alcançado
    return dp[n][maxWeight];
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex2, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP5_Ex2, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}