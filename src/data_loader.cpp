#include "data_loader.h"

#include <cstdio>
#include <fstream>
#include <stdexcept>

namespace knapsack {

namespace {

std::string instance_prefix(int instance_id) {
    if (instance_id < 1 || instance_id > 99) {
        throw std::invalid_argument("instance_id out of range");
    }
    char buf[8];
    snprintf(buf, sizeof(buf), "p%02d", instance_id);
    return std::string(buf);
}

std::string join_path(const std::string& dir, const std::string& name) {
    if (dir.empty()) {
        return name;
    }
    const char last = dir.back();
    if (last == '/' || last == '\\') {
        return dir + name;
    }
    return dir + "/" + name;
}

int read_single_int(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in) {
        throw std::runtime_error("cannot open file: " + filepath);
    }
    int x = 0;
    in >> x;
    return x;
}

std::vector<int> read_int_list(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in) {
        throw std::runtime_error("cannot open file: " + filepath);
    }
    std::vector<int> data;
    int x = 0;
    while (in >> x) {
        data.push_back(x);
    }
    return data;
}

long long compute_profit(const std::vector<int>& values,
                         const std::vector<int>& selection) {
    long long profit = 0;
    const int n = static_cast<int>(values.size());
    for (int i = 0; i < n && i < static_cast<int>(selection.size()); ++i) {
        if (selection[i] != 0) {
            profit += values[i];
        }
    }
    return profit;
}

}  // namespace

Instance load_fsu_instance(const std::string& data_dir, int instance_id) {
    Instance inst;
    inst.id = instance_prefix(instance_id);

    const std::string prefix = inst.id;
    inst.capacity = read_single_int(join_path(data_dir, prefix + "_c.txt"));
    inst.weights = read_int_list(join_path(data_dir, prefix + "_w.txt"));
    inst.values = read_int_list(join_path(data_dir, prefix + "_p.txt"));

    try {
        inst.optimal_selection =
            read_int_list(join_path(data_dir, prefix + "_s.txt"));
        inst.optimal_profit =
            compute_profit(inst.values, inst.optimal_selection);
    } catch (...) {
        inst.optimal_selection.clear();
        inst.optimal_profit = 0;
    }

    return inst;
}

Instance demo_instance() {
    // Classic small example (similar spirit to p02): n=4, C=5
    Instance inst;
    inst.id = "demo";
    inst.weights = {2, 1, 3, 2};
    inst.values = {12, 10, 20, 15};
    inst.capacity = 5;
    inst.optimal_selection = {1, 1, 0, 1};  // items 1,2,4 -> weight 5, profit 37
    inst.optimal_profit = 37;
    return inst;
}

}  // namespace knapsack
