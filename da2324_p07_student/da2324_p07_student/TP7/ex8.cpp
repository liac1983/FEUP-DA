// By: Gonçalo Leão

#include "exercises.h"
#include <limits>
#include <iostream>
#include <vector>

unsigned int calculateTotalDistance(const unsigned int **dists, unsigned int n, const unsigned int *path) {
    unsigned int totalDistance = 0;
    for (unsigned int i = 0; i < n - 1; ++i) {
        totalDistance += dists[path[i]][path[i + 1]];
    }
    // Add distance from the last city back to the initial city
    totalDistance += dists[path[n - 1]][path[0]];
    return totalDistance;
}

void tspBTUtil(const unsigned int **dists, unsigned int n, unsigned int path[], bool visited[], unsigned int currentCity, unsigned int &minDistance, unsigned int currentDistance) {
    if (currentCity == n) {
        // Reached the end of permutation, check if it's a valid tour
        minDistance = std::min(minDistance, currentDistance);
        return;
    }

    for (unsigned int nextCity = 0; nextCity < n; ++nextCity) {
        if (!visited[nextCity]) {
            visited[nextCity] = true;
            path[currentCity] = nextCity;
            unsigned int newDistance = currentDistance + dists[path[currentCity - 1]][nextCity];
            tspBTUtil(dists, n, path, visited, currentCity + 1, minDistance, newDistance);
            visited[nextCity] = false;
        }
    }
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    bool visited[] = {false};
    unsigned int minDistance = std::numeric_limits<unsigned int>::max();

    // Start from city 0
    visited[0] = true;
    path[0] = 0;

    // Start recursive backtracking from the first city
    tspBTUtil(dists, n, path, visited, 1, minDistance, 0);

    return minDistance;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex8, testTSP_4x4_symmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 80);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_4x4_assymmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0, 10, 15, 20}, {5, 0, 9, 10}, {6, 13, 0, 12}, {8, 8, 9,0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 35);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_5x5_symmetric) {
    const unsigned int n = 5;
    const unsigned int dists[n][n] = {{0,12,10,19,8},{12,0,3,7,2},{10,3,0,6,20},{19,7,6,0,4},{8,2,20,4,0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 32);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 2);
    EXPECT_EQ(path[2], 1);
    EXPECT_EQ(path[3], 3);
    EXPECT_EQ(path[4], 4);
}