// By: Gonçalo Leão

#include "exercises.h"
#include <limits>
#include <vector>


void tspBTRec(const unsigned int **dists, unsigned int n, unsigned int curIndex, unsigned
int curDist, unsigned int curPath[], unsigned int &minDist, unsigned int path[]) {
    if (curIndex == n) {
        // add the distance back to the initial mode
        curDist += dists[curPath[n-1]][curPath[0]];
        if(curDist < minDist) {
            minDist = curDist;
            // Copy the current state to the array storing the best state found so far
            for (unsigned int i = 0; i < n; i++) {
                path[i] = curPath[i];
            }
        }
        return ;
    }

    // Try to move to the i-th vertex if the total distance does not exceed the best
    // distance found and the vertex is not yet visited in curPath

    for (unsigned int i = 1; i < n; i++) { // i starts at 1 and not 0 since it is assumed
        // that node 0 is the initial node so it will not be in the middle of the path
        if (curDist + dists[curPath[curIndex -1]][i] < minDist) {
            bool isNewVertex = true;
            for (unsigned int j = 1; j < curIndex; j++) {
                if (curPath[j] == i) {
                    isNewVertex = false;
                    break;
                }
            }
            if (isNewVertex) {
                curPath[curIndex] = i;
                tspBTRec(dists, n, curIndex+1, curDist + dists[curPath[curIndex - 1]][curPath[curIndex]], curPath, minDist, path );
            }
        }

    }
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    unsigned int curPath[10000]; // static memory allocation is faster :)
    unsigned int minDist;
    minDist = std::numeric_limits<unsigned int>::max();

    // Assumes path starts at node 0 ...
    curPath[0] = 0;
    // ... so in the first recursive call curINdex starts at 1 rather than 0
    tspBTRec(dists, n, 1, 0, curPath, minDist, path);
    return minDist;
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