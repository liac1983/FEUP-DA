#include "exercises.h"
#include <iostream>
#include <limits>

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // Create a 2D vector to store the minimum number of coins needed for each value from 0 to T
    std::vector<std::vector<unsigned int>> dp(T + 1, std::vector<unsigned int>(n + 1, std::numeric_limits<unsigned int>::max()));

    // Initialize the base case
    for (unsigned int i = 0; i <= n; ++i)
        dp[0][i] = 0;

    // Iterate through each value from 1 to T
    for (unsigned int t = 1; t <= T; ++t) {
        // Iterate through each coin denomination
        for (unsigned int i = 1; i <= n; ++i) {
            // Check if the current coin denomination can be used for the current value t
            if (C[i - 1] <= t) {
                // Check if using the current coin results in a smaller number of coins needed
                if (dp[t - C[i - 1]][i] != std::numeric_limits<unsigned int>::max() && dp[t - C[i - 1]][i] + 1 < dp[t][i - 1]) {
                    dp[t][i] = dp[t - C[i - 1]][i] + 1;
                }
            }
            // If the current coin is not used, copy the value from the previous coin denomination
            if (dp[t][i - 1] < dp[t][i]) {
                dp[t][i] = dp[t][i - 1];
            }
        }
    }

    // Backtrack to determine which coins were used
    unsigned int t = T;
    unsigned int i = n;
    while (t > 0 && i > 0) {
        if (dp[t][i] != dp[t][i - 1]) {
            usedCoins[i - 1] += 1;
            t -= C[i - 1];
        } else {
            --i;
        }
    }

    // Check if change can be made
    return dp[T][n] != std::numeric_limits<unsigned int>::max();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex1, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];
    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP5_Ex1, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP5_Ex1, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}