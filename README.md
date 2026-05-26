# 0/1 背包 — 动态规划（C++）

## 文件说明

| 文件 | 作用 |
|------|------|
| `include/knapsack_dp.h` | DP 接口 |
| `src/knapsack_dp.cpp` | 一维滚动数组 DP + 路径回溯 |
| `include/data_loader.h` | FSU 数据读取 |
| `src/data_loader.cpp` | 读取 `pXX_c/w/p/s.txt` |
| `src/main.cpp` | 演示 / 批量跑 p01～p08 |

## 编译

```bash
cd knapsack_dp
cmake -B build
cmake --build build
```

Windows (Visual Studio)：

```powershell
cd knapsack_dp
cmake -B build
cmake --build build --config Release
# 可执行文件: build\Release\knapsack_dp.exe 或 build\knapsack_dp.exe
```

## 运行

**未下载数据集时**（内置小例子）：

```bash
./build/knapsack_dp
```

**下载 FSU 数据后**：

将 `Datasets-Course/4.1 Florida State University` 复制到 `data/fsu`，然后：

```bash
./build/knapsack_dp "data/fsu"
```

自定义 DP 容量上限（默认 1000000，p08 的 C 很大会自动跳过）：

```bash
./build/knapsack_dp "data/fsu" 1000000
```

## 算法说明

- 时间复杂度：`O(n * C)`
- 空间复杂度：`O(C)`
- `p08`（C=6404180）超过 `max_capacity` 时返回 `SKIP`，请在报告中说明 DP 不适用。

## 与组员对接

回溯 / 分支限界可复用 `data_loader.h` 读取同一批实例。
