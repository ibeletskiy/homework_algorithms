#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

const int kMin = -1e8;

struct Seg {
  std::vector<std::pair<int, int>> tree;
  int size = 1;

  Seg(int amount) {
    while (size < amount) {
      size *= 2;
    }
    tree.resize(size * 2 - 1, {0, -1});
  }

  std::pair<int, int> Find(int l_find, int r_find, int left, int right, int now) {
    if (left >= r_find || right <= l_find) {
      return {0, -1};
    }
    if (left >= l_find && right <= r_find) {
      return tree[now];
    }
    int mid = left + (right - left) / 2;
    return std::max(Find(l_find, r_find, left, mid, now * 2 + 1),
                    Find(l_find, r_find, mid, right, now * 2 + 2));
  }

  void Set(int pos, std::pair<int, int> val, int left, int right, int now) {
    if (left > pos || right <= pos) {
      return;
    }
    if (right - left == 1) {
      tree[now] = std::max(val, tree[now]);
      return;
    }
    int mid = left + (right - left) / 2;
    Set(pos, val, left, mid, now * 2 + 1);
    Set(pos, val, mid, right, now * 2 + 2);
    tree[now] = std::max(tree[now * 2 + 1], tree[now * 2 + 2]);
  }
};

void Solve() {
  int amount;
  std::cin >> amount;
  std::vector<int> array(amount);
  std::vector<int> values;
  for (int i = 0; i < amount; ++i) {
    std::cin >> array[i];
    values.push_back(array[i]);
  }
  std::sort(values.begin(), values.end());
  values.resize(std::unique(values.begin(), values.end()) - values.begin());
  std::vector<int> dp(amount, 1);
  std::vector<int> prev(amount, -1);
  Seg tree(values.size());
  for (int i = 0; i < amount; ++i) {
    int position = std::lower_bound(values.begin(), values.end(), array[i]) -
                  values.begin();
    std::pair<int, int> answer = tree.Find(position, tree.size, 0, tree.size, 0);
    dp[i] = answer.first + 1;
    prev[i] = answer.second;
    tree.Set(position, {dp[i], i}, 0, tree.size, 0);
  }
  int max = kMin;
  int position = -1;
  std::vector<int> answer;
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
  Solve();
}