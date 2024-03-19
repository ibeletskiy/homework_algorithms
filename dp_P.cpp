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
// const Ll kMin = -1e17;
const Ll kMod = 1e9 + 7;
// const int kMaxn = 1e5;
// const Ll kLg = 20;

std::mt19937_64 rnd(
    std::chrono::steady_clock::now().time_since_epoch().count());

Ll Sum(Ll aa, Ll bb) {
  aa += bb;
  if (aa >= kMod) {
    return aa - kMod;
  }
  return aa;
}

bool IsColumnCorrect(v<v<char>>& field, int column, int mask) {
  for (size_t i = 0; i < field.size(); ++i) {
    if (field[i][column] == '+' && (mask & (1 << i)) == 0) {
      return false;
    }
    if (field[i][column] == '-' && (mask & (1 << i)) != 0) {
      return false;
    }
  }
  return true;
}

int CreateMask(int mask, int length, int begin) {
  int now = begin;
  for (int i = 1; i < length; ++i) {
    int sum = static_cast<int>(((1 << (i - 1)) & mask) != 0) +
              static_cast<int>(((1 << i) & mask) != 0) +
              static_cast<int>(((1 << (i - 1)) & now) != 0);
    if (sum == 0 || sum == 3) {
      return -1;
    }
    now |= ((2 - sum) << i);
  }
  return now;
}

v<int> GetCorrectMasks(int mask, int length) {
  v<int> answer;
  int now = CreateMask(mask, length, 0);
  if (now >= 0) {
    answer.push_back(now);
  }
  now = CreateMask(mask, length, 1);
  if (now >= 0) {
    answer.push_back(now);
  }
  return answer;
}

void Solve() {
  Ll height;
  Ll width;
  std::cin >> height >> width;
  v<v<char>> field(height, v<char>(width));  // + = 1, - = 0
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      char current;
      std::cin >> current;
      field[i][j] = current;
    }
  }
  v<v<Ll>> dp(width, v<Ll>(1 << height, 0));
  for (int mask = 0; mask < (1 << height); ++mask) {
    if (IsColumnCorrect(field, 0, mask)) {
      dp[0][mask] = 1;
    }
  }
  for (int j = 1; j < width; ++j) {
    for (int mask = 0; mask < (1 << height); ++mask) {
      if (!IsColumnCorrect(field, j, mask)) {
        continue;
      }
      v<int> recalc = GetCorrectMasks(mask, height);
      for (auto prev : recalc) {
        if (IsColumnCorrect(field, j - 1, prev)) {
          dp[j][mask] = Sum(dp[j][mask], dp[j - 1][prev]);
        }
      }
    }
  }
  Ll answer = 0;
  for (int mask = 0; mask < (1 << height); ++mask) {
    answer = Sum(answer, dp.back()[mask]);
  }
  std::cout << answer << '\n';
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