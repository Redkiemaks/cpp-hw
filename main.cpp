#include <cstdlib>
#include <iomanip>
#include <iostream>

int main() {
  // Журнал успеваемости: предметы -> студенты -> оценки.
  // int***: у каждого предмета своё число студентов, а у каждого студента своё
  // число оценок, поэтому обычный массив int[S][T][G] не подходит. Три уровня
  // указателей дают book[s][t][j] (j-я оценка t-го студента по предмету s), и
  // при этом каждый уровень имеет свою длину
  // void*: вся память берётся одним malloc. Это сырой блок, в котором лежат
  // данные разных типов (int**, int*, int), поэтому честный тип для него один:
  // void*. Из блока вручную нарезаются три секции: сначала указатели, потом
  // числа (так каждая секция выровнена под свой тип). Выделение одно и
  // освобождение одно, утечка или половинчатое выделение невозможны.
  // Программа считает средний балл по каждому предмету и лучшего студента.
  // Ввод: S T G (предметов, студентов всего, оценок всего), затем для каждого
  // предмета: n (число студентов), и для каждого студента: m и m оценок.
  // Пример ввода:
  //   2 5 12        <- предметов, студентов всего, оценок всего
  //   2             <- предмет 1: 2 студента
  //   3 5 4 5       <- студент 1: 3 оценки (5, 4, 5)
  //   2 3 4         <- студент 2: 2 оценки (3, 4)
  //   3             <- предмет 2: 3 студента
  //   2 4 4         <- студент 1: 2 оценки (4, 4)
  //   1 5           <- студент 2: 1 оценка (5)
  //   4 3 3 3 4     <- студент 3: 4 оценки (3, 3, 3, 4)
  //
  // Вывод:
  //   Subject 1: average 4.20, best student 1 (4.67)
  //   Subject 2: average 3.71, best student 2 (5.00)
  int subjects = 0;
  int students = 0;
  int grades = 0;
  std::cin >> subjects >> students >> grades;
  if (!std::cin || subjects <= 0 || students < 0 || grades < 0) {
    std::cout << "error: bad header\n";
    return 1;
  }

  // Секции блока: S штук int**, T штук int*, потом S + T + G штук int.
  std::size_t bytes = subjects * sizeof(int**) + students * sizeof(int*) +
                      (subjects + students + grades) * sizeof(int);
  void* block = std::malloc(bytes);
  if (block == nullptr) {
    std::cout << "error: out of memory\n";
    return 1;
  }

  char* p = static_cast<char*>(block);       // побайтовый курсор по блоку
  int*** book = static_cast<int***>(block);  // секция 1: таблица предметов
  p += subjects * sizeof(int**);
  int** slots = reinterpret_cast<int**>(p);  // секция 2: списки студентов
  p += students * sizeof(int*);
  int* numbers = reinterpret_cast<int*>(p);  // секция 3: числа

  int* student_count = numbers;       // S чисел: студентов у предмета
  int* records = numbers + subjects;  // записи [m, оценка_1, ..., оценка_m]
  int used_slots = 0;
  int used_ints = 0;
  bool ok = true;
  for (int s = 0; ok && s < subjects; ++s) {
    int n = 0;
    std::cin >> n;
    if (n < 0 || used_slots + n > students) {
      ok = false;
      break;
    }
    student_count[s] = n;
    book[s] = slots + used_slots;
    used_slots += n;
    for (int t = 0; t < n; ++t) {
      int m = 0;
      std::cin >> m;
      if (m < 0 || used_ints + 1 + m > students + grades) {
        ok = false;
        break;
      }
      int* record = records + used_ints;
      record[0] = m;
      for (int j = 1; j <= m; ++j) {
        std::cin >> record[j];
      }
      book[s][t] = record;
      used_ints += 1 + m;
    }
  }
  if (!ok || !std::cin) {
    std::cout << "error: input does not match header\n";
    std::free(block);
    return 1;
  }

  std::cout << std::fixed << std::setprecision(2);
  for (int s = 0; s < subjects; ++s) {
    int sum = 0;
    int count = 0;
    int best = 0;
    double best_avg = 0;
    for (int t = 0; t < student_count[s]; ++t) {
      int m = book[s][t][0];
      int student_sum = 0;
      for (int j = 1; j <= m; ++j) {
        student_sum += book[s][t][j];
      }
      sum += student_sum;
      count += m;
      if (m > 0) {
        double avg = static_cast<double>(student_sum) / m;
        if (best == 0 || avg > best_avg) {
          best = t + 1;
          best_avg = avg;
        }
      }
    }
    std::cout << "Subject " << s + 1 << ": ";
    if (count == 0) {
      std::cout << "no grades\n";
    } else {
      std::cout << "average " << static_cast<double>(sum) / count
                << ", best student " << best << " (" << best_avg << ")\n";
    }
  }

  std::free(block);
  return 0;
}