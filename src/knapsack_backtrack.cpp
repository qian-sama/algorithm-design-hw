#include "knapsack_backtrack.h"

#include <algorithm>

namespace knapsack
{

    namespace
    {

        void backtrack(const std::vector<int> &weights,
                       const std::vector<int> &values,
                       int capacity,
                       int index,
                       long long current_weight,
                       long long current_value,
                       std::vector<int> &current_selection,
                       long long &best_value,
                       std::vector<int> &best_selection,
                       long long &nodes_explored)
        {
            ++nodes_explored;
            const int n = static_cast<int>(weights.size());

            if (index == n)
            {
                if (current_value > best_value)
                {
                    best_value = current_value;
                    best_selection = current_selection;
                }
                return;
            }

            if (current_weight + weights[index] <= capacity)
            {
                current_selection[index] = 1;
                backtrack(weights, values, capacity, index + 1,
                          current_weight + weights[index], current_value + values[index],
                          current_selection, best_value, best_selection, nodes_explored);
            }

            current_selection[index] = 0;
            backtrack(weights, values, capacity, index + 1,
                      current_weight, current_value,
                      current_selection, best_value, best_selection, nodes_explored);
        }

    } // namespace

    BacktrackResult solve_backtrack(const std::vector<int> &weights,
                                    const std::vector<int> &values,
                                    int capacity)
    {
        BacktrackResult result;

        const int n = static_cast<int>(weights.size());
        if (n != static_cast<int>(values.size()))
        {
            result.message = "weights and values size mismatch";
            return result;
        }
        if (capacity < 0)
        {
            result.message = "negative capacity";
            return result;
        }
        if (n == 0)
        {
            result.max_profit = 0;
            result.selected.clear();
            result.time_ms = 0.0;
            result.success = true;
            result.message = "ok";
            result.nodes_explored = 0;
            return result;
        }

        auto start = std::chrono::steady_clock::now();

        std::vector<int> current_selection(n, 0);
        std::vector<int> best_selection(n, 0);
        long long best_value = 0;
        long long nodes_explored = 0;

        backtrack(weights, values, capacity, 0, 0, 0,
                  current_selection, best_value, best_selection, nodes_explored);

        result.max_profit = best_value;
        result.selected = best_selection;
        result.nodes_explored = nodes_explored;

        auto end = std::chrono::steady_clock::now();
        result.time_ms =
            std::chrono::duration<double, std::milli>(end - start).count();
        result.success = true;
        result.message = "ok";
        return result;
    }

} // namespace knapsack