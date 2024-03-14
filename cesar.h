#pragma once

#define _LEN 26

class Cesar_Cypher {
private:
  // expected count of occurances
  double exp_occr[30] = {0};

  // occurances of chars in text
  double occr[30] = {0};

  // encrypted text
  char text[4196];

  // chi_index
  int chi_index = 0;

public:
  // encrypted text file
  char text_file[32] = "text.txt";

  Cesar_Cypher();

  void read_expected_distributions(char *filename);

  void read_encrypted_text(char *filename);

  void occurances_in_text();

  double chi_squared_distance();

  bool decrypt(char text_file[]);

  void init_values();

  void print_text();
};
