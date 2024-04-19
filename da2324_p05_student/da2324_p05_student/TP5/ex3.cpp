#include "exercises.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int editDistance(std::string pattern, std::string text) {
    // Inicializar uma matriz para armazenar os valores da distância de edição
    std::vector<std::vector<int>> dp(pattern.size() + 1, std::vector<int>(text.size() + 1));

    // Inicialização: preencher a primeira linha e a primeira coluna
    for (int i = 0; i <= pattern.size(); ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= text.size(); ++j) {
        dp[0][j] = j;
    }

    // Preencher o restante da matriz
    for (int i = 1; i <= pattern.size(); ++i) {
        for (int j = 1; j <= text.size(); ++j) {
            if (pattern[i - 1] == text[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // Caracteres iguais, sem operação necessária
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                // 1 + mínimo entre deleção, inserção e substituição
            }
        }
    }

    // O valor na última célula contém a distância de edição entre os dois strings
    return dp[pattern.size()][text.size()];
}

float numApproximateStringMatching(std::string filename, std::string toSearch) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return -1.0; // Return an error code
    }

    std::string word;
    int totalDistance = 0;
    int wordCount = 0;

    // Read each word from the file
    while (file >> word) {
        totalDistance += editDistance(toSearch, word);
        ++wordCount;
    }

    file.close();

    // Calculate the average distance
    float averageDistance = static_cast<float>(totalDistance) / static_cast<float>(wordCount);
    return averageDistance;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex3, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}



#define REL_PATH std::string("../TP5/testsEx3/") // relative path to the tests

TEST(TP5_Ex3, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}

