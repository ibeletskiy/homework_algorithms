#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

const int kMax = 1e17;
const int kLg = 20;

void Solve() {
  int floors;
  int planes;
  std::cin >> floors >> planes;
  if (planes == 0) {
    if (floors != 1) {
      std::cout << -1 << '\n';
    } else {
      std::cout << 0 << '\n';
    }
    return;
  }
  std::vector<std::vector<int> > dp(floors + 1, std::vector<int>(std::min(planes, kLg) + 1, kMax));
  std::vector<std::vector<int> > first(floors + 1, std::vector<int>(std::min(planes, kLg) + 1, -1));
  for (int i = 0; i <= floors; ++i) {
    dp[i][1] = 1;
    first[i][1] = 1;
  }
  for (int i = 0; i <= std::min(planes, kLg); ++i) {
    dp[0][i] = 0;
    first[0][i] = 1;
  }
  for (int i = 1; i <= std::min(planes, kLg); ++i) {
    dp[1][i] = 1;
    first[1][i] = 1;
  }
  for (int j = 1; j <= std::min(planes, kLg); ++j) {
    for (int i = 2; i <= floors; ++i) {
      if (std::max(dp[first[i - 1][j] - 1][j - 1], dp[i - first[i - 1][j]][j]) <
          std::max(dp[first[i - 1][j]][j - 1],
                   dp[i - first[i - 1][j] - 1][j])) {
        dp[i][j] = std::max(dp[first[i - 1][j] - 1][j - 1],
                            dp[i - first[i - 1][j]][j]) +
                   1;
        first[i][j] = first[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[first[i - 1][j]][j - 1],
                            dp[i - first[i - 1][j] - 1][j]) +
                   1;
        first[i][j] = first[i - 1][j] + 1;
      }
    }
  }
  std::cout << dp[floors - 1].back() << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const int kPrecision = 10;
  std::cout << std::fixed << std::setprecision(kPrecision);
  Solve();
}