#include <iomanip>
#include <iostream>
double AverageTemp(const int temp[], const int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += temp[i];
  }
  return sum / n;
}
std::pair<int, int> MinMax(const int temp[], const int n) {
  int min = temp[0];
  int max = temp[0];
  for (int i = 0; i < n; i++) {
    if (temp[i] < min) {
      min = temp[i];
    }
    if (temp[i] > max) {
      max = temp[i];
    }
  }
  return std::make_pair(min, max);
}
int CountMinus(const int temp[], const int n) {
  int result = 0;
  for (int i = 0; i < n; i++) {
    if (temp[i] < 0) {
      result++;
    }
  }
  return result;
}
int main() {
  int n;
  std::cin >> n;
  int* temp = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> temp[i];
  }
  std::cout << std::fixed << std::setprecision(1) << AverageTemp(temp, n)
            << '\n';
  std::pair<int, int> minMax = MinMax(temp, n);
  std::cout << minMax.first << " " << minMax.second << '\n';
  std::cout << CountMinus(temp, n) << '\n';
  delete[] temp;
  return 0;
}
