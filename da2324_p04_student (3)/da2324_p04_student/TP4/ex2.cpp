#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include "exercises.h"
#include <string>

void moveDisk(char src, char dest, std::string& moves) {
    moves += src;
    moves += "->";
    moves += dest;
    moves += ",";
}

void hanoiDCUtil(unsigned int n, char src, char aux, char dest, std::string& moves) {
    if (n == 1) {
        moveDisk(src, dest, moves);
        return;
    }

    hanoiDCUtil(n - 1, src, dest, aux, moves);
    moveDisk(src, dest, moves);
    hanoiDCUtil(n - 1, aux, src, dest, moves);
}

std::string hanoiDC(unsigned int n, char src, char dest) {
    std::string moves = "";
    hanoiDCUtil(n, src, 'C', dest, moves); // 'C' is the auxiliary peg
    moves.pop_back(); // Remove the last ','
    return moves;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, testHanoi_height4) {
    std::string moves = hanoiDC(4, 'A', 'B');
    EXPECT_EQ(std::count(moves.begin(),moves.end(),','),14); // there are 15 moves
    EXPECT_EQ(moves,"A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}