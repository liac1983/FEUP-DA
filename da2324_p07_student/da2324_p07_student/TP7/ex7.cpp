// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>
#include <iostream>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

std::vector<Activity> activitySelectionBT(std::vector<Activity> A) {
    std::sort(A.begin(), A.end()); // Sort activities by finish time
    std::vector<Activity> res;
    std::vector<Activity> currentSelection;

    // Helper function to check if the current activity conflicts with any in the selection
    auto conflictsWithCurrentSelection = [&](const Activity &a) {
        for (const Activity &act : currentSelection) {
            if (a.overlaps(act))
                return true;
        }
        return false;
    };

    // Backtracking function
    auto backtrack = [&](unsigned int index) {
        if (index >= A.size()) {
            // Base case: reached end of activities
            if (currentSelection.size() > res.size())
                res = currentSelection; // Update result if current selection is better
            return;
        }

        // Include the activity if it doesn't conflict
        if (!conflictsWithCurrentSelection(A[index])) {
            currentSelection.push_back(A[index]);
            backtrack(index + 1);
            currentSelection.pop_back();
        }

        // Exclude the activity and explore other possibilities
        backtrack(index + 1);
    };

    backtrack(0); // Start backtracking from the first activity
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP7_Ex7, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBT(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}