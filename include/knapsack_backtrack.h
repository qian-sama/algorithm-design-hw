#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace knapsack
{

    struct BacktrackResult
    {
        long long max_profit = 0;
        std::vector<int> selected;
        double time_ms = 0.0;
        bool success = false;
        std::string message;
        long long nodes_explored = 0;
    };

    BacktrackResult solve_backtrack(const std::vector<int> &weights,
                                    const std::vector<int> &values,
                                    int capacity);

} // namespace knapsack