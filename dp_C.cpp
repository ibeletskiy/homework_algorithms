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
using Pll = std::pair<Ll, Ll>;

const Ll kMax = 1e17;
// const Ll kMin = -1e17;
// const Ll kMod = 1e9 + 7;
// const int kMaxn = 1e5;
const Ll kLg = 20;

std::mt19937_64 rnd(
    std::chrono::steady_clock::now().time_since_epoch().count());

void Solve() {
  Ll floors;
  Ll planes;
  std::cin >> floors >> planes;
  if (planes == 0) {
    if (floors != 1) {
      std::cout << -1 << '\n';
    } else {
      std::cout << 0 << '\n';
    }
    return;
  }
  v<v<Ll> > dp(floors + 1, v<Ll>(std::min(planes, kLg) + 1, kMax));
  v<v<Ll> > first(floors + 1, v<Ll>(std::min(planes, kLg) + 1, -1));
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
  /*std::freopen("bst.in", "r", stdin);
  std::freopen("bst.out", "w", stdout);*/
  Solve();
}