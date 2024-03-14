#include "cesar.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

void Cesar_Cypher::read_expected_distributions(char filename[]) {
  std::ifstream filex(filename);

  // read variable
  double d;

  // index of distribution array
  int index = 0;

  if (filex.is_open()) {
    while (filex.good()) {
      filex >> d;
      this->exp_occr[index++] = d;
    }
  }

  filex.close();
}

void Cesar_Cypher::occurances_in_text() {
  for (size_t i = 0; i < strlen(this->text); i++) {
    char c = this->text[i];
    // A - 65, a - 97
    if (c >= 'A' and c <= 'Z')
      c += ('a' - 'A');

    if (c >= 'a' and c <= 'z') {
      int index = c - 'a';
      this->occr[index]++;
    }
  }
}

double Cesar_Cypher::chi_squared_distance() {
  // formula sum (ci-ei)^2/ei
  double sum = 0;

  for (int i = 0; i < _LEN; i++) {
    double delta = this->exp_occr[i] - this->occr[i];
    sum += delta * delta / this->exp_occr[i];
  }

  return sum;
}

void Cesar_Cypher::read_encrypted_text(char *filename) {
  memset(this->text, '\0', sizeof(this->text));

  ifstream file(filename);
  int index = 0;

  while (!file.eof()) {
    file.get(this->text[index++]);
  }
  occurances_in_text();
}

void Cesar_Cypher::print_text() {
  fstream file;
  file.open("output.txt", std::ios::out);

  for (size_t i = 0; i < strlen(this->text); i++) {
    if (isalpha(this->text[i])) {
      int c = this->text[i];

      int low = 'a', high = 'z';

      if (c >= 'A' and c <= 'Z') {
        low = 'A';
        high = 'Z';
      }

      c += chi_index;
      if (c > high)
        c += low - high - 1;
      this->text[i] = c;
    }
    file << this->text[i];
  }
  file.close();
}

bool Cesar_Cypher::decrypt(char text_file[]) {
  init_values();

  read_encrypted_text(text_file);

  this->chi_index = 0;
  double chi_sq = chi_squared_distance();

  for (int i = 1; i < _LEN; i++) {
    double first_copy = this->exp_occr[0];

    for (int j = 0; j < _LEN - 1; j++) {
      this->exp_occr[j] = this->exp_occr[j + 1];
    }

    this->exp_occr[_LEN - 1] = first_copy;

    double new_sq = chi_squared_distance();

    if (new_sq < chi_sq) {
      this->chi_index = i;
      chi_sq = new_sq;
    }
  }

  print_text();
  return true;
}

void Cesar_Cypher::init_values() {
  char occr_file[32] = "distribution.txt";
  read_expected_distributions(occr_file);

  for (int i = 0; i < _LEN; i++) {
    this->occr[i] = 0;
  }
}

Cesar_Cypher::Cesar_Cypher() { init_values(); }
