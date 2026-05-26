#pragma once

#include <chrono>
#include <string>
#include <utility>
#include <vector>

namespace knapsack {

struct DpResult {
    long long max_profit = 0;
    std::vector<int> selected;  // selected[i] == 1 means item i is taken
    double time_ms = 0.0;
    bool success = false;
    std::string message;
};

// Classic 0/1 knapsack DP: O(n * C) time, O(C) space (1D rolling array).
// Returns failure when capacity is negative or too large for practical DP.
DpResult solve_dp(const std::vector<int>& weights,
                  const std::vector<int>& values,
                  int capacity,
                  long long max_capacity = 1'000'000);

}  // namespace knapsack
