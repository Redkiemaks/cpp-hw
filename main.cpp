#include <cstring>
#include <iomanip>
#include <iostream>
const int rows = 5;
const int cols = 10;
void Clear(char display[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      display[i][j] = ' ';
    }
  }
}
bool InBounds(int x, int y) { return x >= 0 && x < cols && y >= 0 && y < rows; }
bool Put(char display[rows][cols], int x, int y, char c) {
  if (InBounds(x, y)) {
    display[y][x] = c;
    return true;
  }
  return false;
}
bool Text(char display[rows][cols], int x, int y, char word[]) {
  int len = static_cast<int>(std::strlen(word));
  if (InBounds(x + len - 1, y) && InBounds(x, y)) {
    for (int i = 0; i < len; i++) {
      display[y][x + i] = word[i];
    }
    return true;
  }
  return false;
}
void Print(char display[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << display[i][j];
    }
    std::cout << '\n';
  }
}

int main() {
  char display[rows][cols];
  Clear(display);
  char command[256];
  while (std::cin >> std::setw(256) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      Clear(display);
    } else if (std::strcmp(command, "put") == 0) {
      int x, y;
      char c;
      std::cin >> x >> y >> c;
      if (!Put(display, x, y, c)) {
        std::cout << "error" << '\n';
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x, y;
      char word[256];
      std::cin >> x >> y >> std::setw(256) >> word;
      if (!Text(display, x, y, word)) {
        std::cout << "error" << '\n';
      }
    } else if (std::strcmp(command, "print") == 0) {
      Print(display);
    }
  }
  return 0;
}
