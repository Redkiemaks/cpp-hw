#include <cstring>
#include <iomanip>
#include <iostream>

void deposit(int& bank, int k) {
  if (k <= 0) {
    std::cout << "error" << '\n';
    return;
  }
  bank += k;
}

void balance(int& bank, int) { std::cout << bank << '\n'; }

void withdraw(int& bank, int k) {
  if (k > bank || k <= 0) {
    std::cout << "error" << '\n';
  } else {
    bank -= k;
  }
}

void reset(int& bank, int) { bank = 0; }

void Double(int& bank, int) { bank *= 2; }

struct Command {
  const char* name;
  void (*func)(int&, int);
  bool read;
};

const Command commands[] = {
    {"deposit", deposit, true},   {"balance", balance, false},
    {"withdraw", withdraw, true}, {"reset", reset, false},
    {"double", Double, false},
};
const int command_count = sizeof(commands) / sizeof(commands[0]);

int main() {
  int bank = 0;
  char name[256];
  while (std::cin >>  std::setw(256) >> name) {
    if (std::strcmp(name, "stop") == 0) {
      break;
    }
    bool found = false;
    for (int i = 0; i < command_count; ++i) {
      if (std::strcmp(name, commands[i].name) == 0) {
        int k = 0;
        if (commands[i].read) {
          std::cin >> k;
        }
        commands[i].func(bank, k);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "error" << '\n';
    }
  }
  return 0;
}
