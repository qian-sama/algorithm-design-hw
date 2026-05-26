#include "data_loader.h"
#include "knapsack_dp.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

namespace {

void print_result(const knapsack::Instance& inst, const knapsack::DpResult& r) {
    std::cout << std::left << std::setw(6) << inst.id << "  "
              << "n=" << inst.weights.size() << "  "
              << "C=" << inst.capacity << "  "
              << "profit=" << r.max_profit << "  "
              << "time_ms=" << std::fixed << std::setprecision(3) << r.time_ms
              << "  ";

    if (!r.success) {
        std::cout << "status=SKIP(" << r.message << ")\n";
        return;
    }

    if (inst.optimal_profit > 0) {
        const bool ok = (r.max_profit == inst.optimal_profit);
        std::cout << "optimal=" << inst.optimal_profit << "  "
                  << "correct=" << (ok ? "YES" : "NO") << "\n";
    } else {
        std::cout << "status=OK\n";
    }
}

void run_on_instance(const knapsack::Instance& inst, long long max_c) {
    const auto r = knapsack::solve_dp(inst.weights, inst.values, inst.capacity, max_c);
    print_result(inst, r);
}

}  // namespace

int main(int argc, char* argv[]) {
    // Usage:
    //   knapsack_dp                         -> run built-in demo
    //   knapsack_dp <data_dir>              -> run p01..p08 under data_dir
    //   knapsack_dp <data_dir> <max_C>      -> custom DP capacity limit
    //
    // Example after you download dataset:
    //   knapsack_dp "data/fsu" 1000000

    long long max_capacity = 1'000'000;
    std::string data_dir;

    if (argc >= 2) {
        data_dir = argv[1];
    }
    if (argc >= 3) {
        max_capacity = std::atoll(argv[2]);
    }

    std::cout << "=== 0/1 Knapsack - Dynamic Programming ===\n";
    std::cout << "max_capacity for DP = " << max_capacity << "\n\n";

    if (data_dir.empty()) {
        std::cout << "[demo] no data_dir provided, using built-in example.\n";
        std::cout << "After downloading FSU data, run:\n";
        std::cout << "  knapsack_dp \"path/to/4.1 Florida State University\"\n\n";

        const auto demo = knapsack::demo_instance();
        run_on_instance(demo, max_capacity);
        return 0;
    }

    std::cout << "data_dir = " << data_dir << "\n\n";
    std::cout << std::left << std::setw(6) << "inst"
              << "details\n";
    std::cout << "----------------------------------------------\n";

    for (int id = 1; id <= 8; ++id) {
        try {
            const auto inst = knapsack::load_fsu_instance(data_dir, id);
            run_on_instance(inst, max_capacity);
        } catch (const std::exception& ex) {
            std::cout << "p" << std::setw(2) << std::setfill('0') << id
                      << "  ERROR: " << ex.what() << "\n";
            std::cout << std::setfill(' ');
        }
    }

    return 0;
}
