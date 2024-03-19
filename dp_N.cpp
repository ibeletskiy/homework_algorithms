#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define debug(a) std::cerr << #a << ": " << a << '\n';
#define all(a) (a).begin(), (a).end()
#define v std::vector

using Ll = long long;
using Str = std::string;
using Pll = std::pair<int, int>;

const int kMax = 1e8;
// const int kMin = -1e17;
// const int kMod = 1e9 + 7;
// const int kMaxn = 1e5;
// const int kLg = 20;

std::mt19937_64 rnd(
    std::chrono::steady_clock::now().time_since_epoch().count());

struct Position {
  int first_len;
  int second_len;
  int amount;

  Position(int ii, int jj, int kk)
      : first_len(ii), second_len(jj), amount(kk) {}
};

void Update(Str& first, Str& second, v<v<v<int>>>& dp, Position pos) {
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
  Str first;
  Str second;
  std::cin >> first >> second;
  int actions;
  std::cin >> actions;
  v<v<v<int>>> dp(first.size() + 1,
                  v<v<int>>(second.size() + 1, v<int>(actions + 1, kMax)));
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
  /*std::freopen("bst.in", "r", stdin);
  std::freopen("bst.out", "w", stdout);*/
  Solve();
}