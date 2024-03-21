#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

const int kMax = 1e8;

struct Position {
  int first_len;
  int second_len;
  int amount;

  Position(int ii, int jj, int kk)
      : first_len(ii), second_len(jj), amount(kk) {}
};

void Update(std::string& first, std::string& second, std::vector<std::vector<std::vector<int>>>& dp, Position pos) {
  if (pos.first_len == 0 || pos.second_len == 0) {
    if (pos.first_len == 0 && pos.second_len == 0) {
      dp[pos.first_len][pos.second_len][pos.amount] = 0;
    }
    if (pos.first_len == 0 && pos.second_len <= pos.amount) {
      dp[pos.first_len][pos.second_len][pos.amount] = 0;
    }
    if (pos.second_len == 0 && pos.first_len <= pos.amount) {
      dp[pos.first_len][pos.second_len][pos.amount] = 0;
    }
    return;
  }
  dp[pos.first_len][pos.second_len][pos.amount] =
      std::min(dp[pos.first_len][pos.second_len][pos.amount],
               dp[pos.first_len][pos.second_len - 1][pos.amount - 1]);
  dp[pos.first_len][pos.second_len][pos.amount] =
      std::min(dp[pos.first_len][pos.second_len][pos.amount],
               dp[pos.first_len - 1][pos.second_len][pos.amount - 1]);
  dp[pos.first_len][pos.second_len][pos.amount] =
      std::min(dp[pos.first_len][pos.second_len][pos.amount],
               dp[pos.first_len - 1][pos.second_len - 1][pos.amount - 1]);
  if (first[pos.first_len - 1] == second[pos.second_len - 1]) {
    dp[pos.first_len][pos.second_len][pos.amount] =
        std::min(dp[pos.first_len][pos.second_len][pos.amount],
                 dp[pos.first_len - 1][pos.second_len - 1][pos.amount]);
  } else {
    dp[pos.first_len][pos.second_len][pos.amount] =
        std::min(dp[pos.first_len][pos.second_len][pos.amount],
                 dp[pos.first_len - 1][pos.second_len - 1][pos.amount] + 1);
  }
}

void Solve() {
  std::string first;
  std::string second;
  std::cin >> first >> second;
  int actions;
  std::cin >> actions;
  std::vector<std::vector<std::vector<int>>> dp(first.size() + 1,
                  std::vector<std::vector<int>>(second.size() + 1, std::vector<int>(actions + 1, kMax)));
  for (int j = 0; j <= static_cast<int>(second.size()) && j <= actions; ++j) {
    dp[0][j][j] = 0;
  }
  for (size_t i = 1; i <= std::min(first.size(), second.size()); ++i) {
    int count = 0;
    for (size_t j = 0; j < i; ++j) {
      if (first[j] != second[j]) {
        ++count;
      }
    }
    dp[i][i][0] = count;
  }
  for (int k = 1; k <= actions; ++k) {
    for (size_t i = 0; i <= first.size(); ++i) {
      for (size_t j = 0; j <= second.size(); ++j) {
        Update(first, second, dp, Position(i, j, k));
      }
    }
  }
  int ans = kMax;
  for (int i = 0; i <= actions; ++i) {
    ans = std::min(ans, dp[first.size()][second.size()][i]);
  }
  if (ans == kMax) {
    std::cout << -1 << '\n';
  } else {
    std::cout << ans << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const int kPrecision = 10;
  std::cout << std::fixed << std::setprecision(kPrecision);
  Solve();
}