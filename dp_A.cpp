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
#define aLl(a) (a).begin(), (a).end()
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

struct Seg {
  v<Pll> tree;
  Ll size = 1;

  Seg(Ll amount) {
    while (size < amount) {
      size *= 2;
    }
    tree.resize(size * 2 - 1, {0, -1});
  }

  Pll Find(Ll l_find, Ll r_find, Ll left, Ll right, Ll now) {
    if (left >= r_find || right <= l_find) {
      return {0, -1};
    }
    if (left >= l_find && right <= r_find) {
      return tree[now];
    }
    Ll mid = left + (right - left) / 2;
    return std::max(Find(l_find, r_find, left, mid, now * 2 + 1),
                    Find(l_find, r_find, mid, right, now * 2 + 2));
  }

  void Set(Ll pos, Pll val, Ll left, Ll right, Ll now) {
    if (left > pos || right <= pos) {
      return;
    }
    if (right - left == 1) {
      tree[now] = std::max(val, tree[now]);
      return;
    }
    Ll mid = left + (right - left) / 2;
    Set(pos, val, left, mid, now * 2 + 1);
    Set(pos, val, mid, right, now * 2 + 2);
    tree[now] = std::max(tree[now * 2 + 1], tree[now * 2 + 2]);
  }
};

void Solve() {
  Ll amount;
  std::cin >> amount;
  std::vector<Ll> array(amount);
  std::vector<Ll> values;
  for (int i = 0; i < amount; ++i) {
    std::cin >> array[i];
    values.push_back(array[i]);
  }
  std::sort(aLl(values));
  values.resize(std::unique(aLl(values)) - values.begin());
  std::vector<Ll> dp(amount, 1);
  std::vector<Ll> prev(amount, -1);
  Seg tree(values.size());
  for (int i = 0; i < amount; ++i) {
    Ll position = std::lower_bound(values.begin(), values.end(), array[i]) -
                  values.begin();
    Pll answer = tree.Find(position, tree.size, 0, tree.size, 0);
    dp[i] = answer.first + 1;
    prev[i] = answer.second;
    tree.Set(position, {dp[i], i}, 0, tree.size, 0);
  }
  Ll max = kMin;
  Ll position = -1;
  std::vector<Ll> answer;
  for (int i = 0; i < amount; ++i) {
    if (max < dp[i]) {
      max = dp[i];
      position = i;
    }
  }
  while (position != -1) {
    answer.push_back(position);
    position = prev[position];
  }
  std::reverse(answer.begin(), answer.end());
  std::cout << max << '\n';
  for (auto now : answer) {
    std::cout << now + 1 << ' ';
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