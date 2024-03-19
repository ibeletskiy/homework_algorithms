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
// const int kLg = 20;

/*int without_last = mask & (mask - 1);
        int last = mask ^ without_last;
        int number = power[last];
        left[mask] = left[without_last] & static_cast<int>(((gr[number] &
   without_last) == without_last)); answer += left[mask];*/

std::mt19937_64 rnd(
    std::chrono::steady_clock::now().time_since_epoch().count());

void Relax(Ll& opt, Ll& sum, Ll& pos, int& kk) {
  if (opt > sum) {
    opt = sum;
    pos = kk;
  }
}

void Solve() {
  Ll size;
  Ll count;
  std::cin >> size >> count;
  v<Ll> list(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> list[i];
  }
  v<v<Ll>> seg(size, v<Ll>(size, 0));
  v<v<Ll>> point(size, v<Ll>(size, 0));
  for (int i = 0; i < size; ++i) {
    for (int j = i; j < size; ++j) {
      Ll sum = 0;
      for (int k = i; k <= j; ++k) {
        sum += list[k] - list[i];
      }
      Ll opt = sum;
      Ll pos = i;
      for (int k = i + 1; k <= j; ++k) {
        sum += (list[k] - list[k - 1]) * (k - i);
        sum -= (list[k] - list[k - 1]) * (j - k + 1);
        Relax(opt, sum, pos, k);
      }
      seg[i][j] = opt;
      point[i][j] = pos;
    }
  }
  v<v<Ll>> dp(size + 1, v<Ll>(count + 1, kMax));
  v<v<Ll>> prev(size + 1, v<Ll>(count + 1, -1));
  dp[0][0] = 0;
  for (int i = 1; i <= size; ++i) {
    for (int j = 1; j <= count; ++j) {
      for (int k = 0; k < i; ++k) {
        if (dp[i][j] > dp[k][j - 1] + seg[k][i - 1]) {
          dp[i][j] = dp[k][j - 1] + seg[k][i - 1];
          prev[i][j] = k;
        }
      }
    }
  }
  Ll pos = size;
  v<Ll> answer;
  for (int i = count; i > 0; --i) {
    answer.push_back(point[prev[pos][i]][pos - 1]);
    pos = prev[pos][i];
  }
  std::reverse(all(answer));
  std::cout << dp[size][count] << '\n';
  for (auto now : answer) {
    std::cout << list[now] << ' ';
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