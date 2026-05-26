#include "knapsack_dp.h"

#include <algorithm>
#include <limits>

namespace knapsack {

namespace {

constexpr long long kInf = std::numeric_limits<long long>::max() / 4;

}  // namespace

DpResult solve_dp(const std::vector<int>& weights,
                  const std::vector<int>& values,
                  int capacity,
                  long long max_capacity) {
    DpResult result;

    const int n = static_cast<int>(weights.size());
    if (n != static_cast<int>(values.size())) {
        result.message = "weights and values size mismatch";
        return result;
    }
    if (capacity < 0) {
        result.message = "negative capacity";
        return result;
    }
    if (static_cast<long long>(capacity) > max_capacity) {
        result.message = "capacity too large for DP (exceeds max_capacity)";
        return result;
    }

    auto start = std::chrono::steady_clock::now();

    // dp[c] = max profit with capacity c
    std::vector<long long> dp(capacity + 1, 0);
    // path[c] = last item index used to reach dp[c], -1 if unreachable from items
    std::vector<int> path(capacity + 1, -1);
    std::vector<int> from_cap(capacity + 1, -1);

    for (int i = 0; i < n; ++i) {
        const int w = weights[i];
        const int v = values[i];
        if (w < 0 || v < 0) {
            result.message = "negative weight or value not supported";
            return result;
        }
        if (w > capacity) {
            continue;
        }

        for (int c = capacity; c >= w; --c) {
            const long long candidate = dp[c - w] + v;
            if (candidate > dp[c]) {
                dp[c] = candidate;
                path[c] = i;
                from_cap[c] = c - w;
            }
        }
    }

    result.max_profit = dp[capacity];

    // Reconstruct one optimal solution by backtracking path pointers.
    result.selected.assign(n, 0);
    int c = capacity;
    while (c > 0 && path[c] != -1) {
        const int item = path[c];
        result.selected[item] = 1;
        c = from_cap[c];
    }

    auto end = std::chrono::steady_clock::now();
    result.time_ms =
        std::chrono::duration<double, std::milli>(end - start).count();
    result.success = true;
    result.message = "ok";
    return result;
}

}  // namespace knapsack
