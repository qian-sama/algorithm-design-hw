#include "data_loader.h"
#include "knapsack_dp.h"
#include "knapsack_backtrack.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

namespace
{

    void print_result(const knapsack::Instance &inst, const knapsack::DpResult &r)
    {
        std::cout << std::left << std::setw(6) << inst.id << "  "
                  << "n=" << inst.weights.size() << "  "
                  << "C=" << inst.capacity << "  "
                  << "profit=" << r.max_profit << "  "
                  << "time_ms=" << std::fixed << std::setprecision(3) << r.time_ms
                  << "  ";

        if (!r.success)
        {
            std::cout << "status=SKIP(" << r.message << ")\n";
            return;
        }

        if (inst.optimal_profit > 0)
        {
            const bool ok = (r.max_profit == inst.optimal_profit);
            std::cout << "optimal=" << inst.optimal_profit << "  "
                      << "correct=" << (ok ? "YES" : "NO") << "\n";
        }
        else
        {
            std::cout << "status=OK\n";
        }
    }

    void print_result(const knapsack::Instance &inst, const knapsack::BacktrackResult &r)
    {
        std::cout << std::left << std::setw(6) << inst.id << "  "
                  << "n=" << inst.weights.size() << "  "
                  << "C=" << inst.capacity << "  "
                  << "profit=" << r.max_profit << "  "
                  << "time_ms=" << std::fixed << std::setprecision(3) << r.time_ms << "  "
                  << "nodes=" << r.nodes_explored << "  ";

        if (!r.success)
        {
            std::cout << "status=SKIP(" << r.message << ")\n";
            return;
        }

        if (inst.optimal_profit > 0)
        {
            const bool ok = (r.max_profit == inst.optimal_profit);
            std::cout << "optimal=" << inst.optimal_profit << "  "
                      << "correct=" << (ok ? "YES" : "NO") << "\n";
        }
        else
        {
            std::cout << "status=OK\n";
        }
    }

    void run_on_instance(const knapsack::Instance &inst, long long max_c, const std::string &algorithm)
    {
        if (algorithm == "dp")
        {
            const auto r = knapsack::solve_dp(inst.weights, inst.values, inst.capacity, max_c);
            print_result(inst, r);
        }
        else if (algorithm == "backtrack")
        {
            const auto r = knapsack::solve_backtrack(inst.weights, inst.values, inst.capacity);
            print_result(inst, r);
        }
    }

} // namespace

int main(int argc, char *argv[])
{
    // Usage:
    //   knapsack_dp                         -> run built-in demo with DP
    //   knapsack_dp <data_dir>              -> run p01..p08 under data_dir with DP
    //   knapsack_dp <data_dir> <max_C>      -> custom DP capacity limit
    //   knapsack_dp <data_dir> <algorithm>  -> choose algorithm (dp/backtrack)
    //   knapsack_dp <data_dir> <max_C> <algorithm> -> custom DP capacity limit + choose algorithm
    //
    // Example after you download dataset:
    //   knapsack_dp "data/fsu"
    //   knapsack_dp "data/fsu" 1000000
    //   knapsack_dp "data/fsu" backtrack
    //   knapsack_dp "data/fsu" 1000000 dp

    long long max_capacity = 1'000'000;
    std::string data_dir;
    std::string algorithm = "dp";

    if (argc >= 2)
    {
        data_dir = argv[1];
    }
    if (argc >= 3)
    {
        std::string arg2 = argv[2];
        if (arg2 == "dp" || arg2 == "backtrack")
        {
            algorithm = arg2;
        }
        else
        {
            max_capacity = std::atoll(argv[2]);
            if (argc >= 4)
            {
                algorithm = argv[3];
            }
        }
    }

    std::cout << "=== 0/1 Knapsack - " << (algorithm == "dp" ? "Dynamic Programming" : "Backtracking") << " ===\n";
    if (algorithm == "dp")
    {
        std::cout << "max_capacity for DP = " << max_capacity << "\n";
    }
    std::cout << "\n";

    if (data_dir.empty())
    {
        std::cout << "[demo] no data_dir provided, using built-in example.\n";
        std::cout << "After downloading FSU data, run:\n";
        std::cout << "  knapsack_dp \"path/to/4.1 Florida State University\"\n";
        std::cout << "  knapsack_dp \"path/to/4.1 Florida State University\" backtrack\n\n";

        const auto demo = knapsack::demo_instance();
        run_on_instance(demo, max_capacity, algorithm);
        return 0;
    }

    std::cout << "data_dir = " << data_dir << "\n\n";
    std::cout << std::left << std::setw(6) << "inst"
              << "details\n";
    std::cout << "----------------------------------------------\n";

    for (int id = 1; id <= 8; ++id)
    {
        try
        {
            const auto inst = knapsack::load_fsu_instance(data_dir, id);
            run_on_instance(inst, max_capacity, algorithm);
        }
        catch (const std::exception &ex)
        {
            std::cout << "p" << std::setw(2) << std::setfill('0') << id
                      << "  ERROR: " << ex.what() << "\n";
            std::cout << std::setfill(' ');
        }
    }

    return 0;
}
