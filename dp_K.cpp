#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

const int64_t kMin = -1e17;

void Solve() {
  int amount;
  int64_t sum_weight;
  std::cin >> amount >> sum_weight;
  std::vector<int64_t> weights(amount);
  std::vector<int64_t> costs(amount);
  for (int i = 0; i < amount; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < amount; ++i) {
    std::cin >> costs[i];
  }
  std::vector<std::vector<int64_t>> dp(amount + 1,
                                  std::vector<int64_t>(sum_weight + 1, kMin));
  std::vector<std::vector<int64_t>> is_taken(amount + 1,
                                        std::vector<int64_t>(sum_weight + 1, 0));
  dp[0][0] = 0;
  for (int i = 1; i <= amount; ++i) {
    for (int j = 0; j <= sum_weight; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j - weights[i - 1] >= 0) {
        if (dp[i][j] < dp[i - 1][j - weights[i - 1]] + costs[i - 1]) {
          dp[i][j] = dp[i - 1][j - weights[i - 1]] + costs[i - 1];
          is_taken[i][j] = 1;
        }
      }
    }
  }
  int64_t max = kMin;
  int64_t weight = -1;
  for (int j = 0; j <= sum_weight; ++j) {
    if (max < dp[amount][j]) {
      max = dp[amount][j];
      weight = j;
    }
  }
  std::vector<int64_t> answer;
  int64_t layer = amount;
  while (weight != 0) {
    if (is_taken[layer][weight] != 0) {
      answer.push_back(layer);
      weight -= weights[layer - 1];
    }
    --layer;
  }
  std::reverse(answer.begin(), answer.end());
  for (auto now : answer) {
    std::cout << now << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  const int kPrecision = 10;
  std::cout << std::fixed << std::setprecision(kPrecision);
  Solve();
}