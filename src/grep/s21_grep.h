#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int e, i, v, c, l, n, h, s, f, o;
  size_t files;
  char patterns[5000];
};

int find_flag(int argc, char *argv[], struct flags *FLAG);
void print_file(struct flags FLAG, char *file_name, FILE *file);

#endif  // SRC_S21_GREP_H_
