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

// const Ll kMax = 1e17;
const Ll kMin = -1e17;
// const Ll kMod = 1e9 + 7;
// const int kMaxn = 1e5;
// const int kLg = 20;

std::mt19937_64 rnd(
    std::chrono::steady_clock::now().time_since_epoch().count());

void Solve() {
  Ll amount;
  Ll sum_weight;
  std::cin >> amount >> sum_weight;
  std::vector<Ll> weights(amount);
  std::vector<Ll> costs(amount);
  for (int i = 0; i < amount; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < amount; ++i) {
    std::cin >> costs[i];
  }
  std::vector<std::vector<Ll>> dp(amount + 1,
                                  std::vector<Ll>(sum_weight + 1, kMin));
  std::vector<std::vector<Ll>> is_taken(amount + 1,
                                        std::vector<Ll>(sum_weight + 1, 0));
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
  Ll max = kMin;
  Ll weight = -1;
  for (int j = 0; j <= sum_weight; ++j) {
    if (max < dp[amount][j]) {
      max = dp[amount][j];
      weight = j;
    }
  }
  std::vector<Ll> answer;
  Ll layer = amount;
  while (weight != 0) {
    if (is_taken[layer][weight] != 0) {
      answer.push_back(layer);
      weight -= weights[layer - 1];
    }
    --layer;
  }
  std::reverse(all(answer));
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
  /*std::freopen("bst.in", "r", stdin);
  std::freopen("bst.out", "w", stdout);*/
  Solve();
}