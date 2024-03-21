#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

const int64_t kMod = 1e9 + 7;

int64_t Sum(int64_t aa, int64_t bb) {
  aa += bb;
  if (aa >= kMod) {
    return aa - kMod;
  }
  return aa;
}

bool IsColumnCorrect(std::vector<std::vector<char>>& field, int column, int mask) {
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

std::vector<int> GetCorrectMasks(int mask, int length) {
  std::vector<int> answer;
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
  int64_t height;
  int64_t width;
  std::cin >> height >> width;
  std::vector<std::vector<char>> field(height, std::vector<char>(width));  // + := 1, - := 0
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      char current;
      std::cin >> current;
      field[i][j] = current;
    }
  }
  std::vector<std::vector<int64_t>> dp(width, std::vector<int64_t>(1 << height, 0));
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
      std::vector<int> recalc = GetCorrectMasks(mask, height);
      for (auto prev : recalc) {
        if (IsColumnCorrect(field, j - 1, prev)) {
          dp[j][mask] = Sum(dp[j][mask], dp[j - 1][prev]);
        }
      }
    }
  }
  int64_t answer = 0;
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
  Solve();
}