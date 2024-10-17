#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>

struct flags {
  int s, n, b, e, t, v;
};

void find_flag(int argc, char* argv[], struct flags* FLAG);
void open_file(int argc, char* argv[], struct flags FLAG);
void print_file(FILE* file, struct flags FLAG);

#endif  // SRC_S21_CAT_H_
