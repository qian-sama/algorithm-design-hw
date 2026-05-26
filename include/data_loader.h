#pragma once

#include <string>
#include <vector>

namespace knapsack {

struct Instance {
    std::string id;              // e.g. "p01"
    std::vector<int> weights;
    std::vector<int> values;
    int capacity = 0;
    std::vector<int> optimal_selection;  // from *_s.txt, may be empty
    long long optimal_profit = 0;        // computed from selection + values
};

// Load Florida State University format: pXX_c/w/p/s.txt under data_dir.
// data_dir should point to folder "4.1 Florida State University" or your copy "data/fsu".
Instance load_fsu_instance(const std::string& data_dir, int instance_id);

// Built-in tiny example when dataset files are not downloaded yet.
Instance demo_instance();

}  // namespace knapsack
