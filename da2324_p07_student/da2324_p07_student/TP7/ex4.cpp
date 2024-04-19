#include "exercises.h"

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];
}

#include <iostream>

void  Labyrinth::print() const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << labyrinth[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Labyrinth::findGoal(int x, int y) {
    // Base case: If current position is the exit, print message and return true
    if (labyrinth[x][y] == MAZE_EXIT) {
        std::cout << "Exit found at position (" << x << ", " << y << ")!" << std::endl;
        return true;
    }

    // Mark current position as visited
    visited[x][y] = true;

    // Explore adjacent cells (up, down, left, right)
    if (x > 0 && labyrinth[x - 1][y] != MAZE_WALL && !visited[x - 1][y]) {
        if (findGoal(x - 1, y)) return true; // Move up
    }
    if (x < 9 && labyrinth[x + 1][y] != MAZE_WALL && !visited[x + 1][y]) {
        if (findGoal(x + 1, y)) return true; // Move down
    }
    if (y > 0 && labyrinth[x][y - 1] != MAZE_WALL && !visited[x][y - 1]) {
        if (findGoal(x, y - 1)) return true; // Move left
    }
    if (y < 9 && labyrinth[x][y + 1] != MAZE_WALL && !visited[x][y + 1]) {
        if (findGoal(x, y + 1)) return true; // Move right
    }

    // If no adjacent cell leads to the exit, backtrack
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex4, testLabyrinthPossible) {
    // This test assumes that the mazes only have a possible path to the exit
    int lab1[10][10] ={
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,1,1,0,1,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,1,1,1,1,0},
        {0,1,1,1,0,0,1,0,1,0},
        {0,1,0,0,0,0,1,0,1,0},
        {0,1,1,1,0,0,1,2,0,0},
        {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),true);
}

TEST(TP7_Ex4, testLabyrinthImpossible) {
    int lab1[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),false);
}