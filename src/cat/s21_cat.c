#include "s21_cat.h"

int main(int argc, char* argv[]) {
  struct flags FLAG = {0};
  find_flag(argc, argv, &FLAG);
  open_file(argc, argv, FLAG);
  return 0;
}

void find_flag(int argc, char* argv[], struct flags* FLAG) {
  int flag;
  struct option long_options[] = {{"squeeze-blank", 0, 0, 's'},
                                  {"number", 0, 0, 'n'},
                                  {"number-nonblank", 0, 0, 'b'},
                                  {0, 0, 0, 0}};
  while ((flag = getopt_long(argc, argv, "snbvetET", long_options, NULL)) !=
         -1) {
    switch (flag) {
      case 's':
        FLAG->s = 1;
        break;
      case 'n':
        FLAG->n = 1;
        break;
      case 'b':
        FLAG->b = 1;
        break;
      case 'v':
        FLAG->v = 1;
        break;
      case 'e':
        FLAG->e = 1;
        FLAG->v = 1;
        break;
      case 't':
        FLAG->t = 1;
        FLAG->v = 1;
        break;
      case 'E':
        FLAG->e = 1;
        break;
      case 'T':
        FLAG->t = 1;
        break;
    }
    if (FLAG->b == 1) FLAG->n = 0;
  }
}

void open_file(int argc, char* argv[], struct flags FLAG) {
  FILE* file = NULL;
  while (optind < argc) {
    file = fopen(argv[optind], "r");
    if (file) {
      print_file(file, FLAG);
      fclose(file);
    } else {
      fprintf(stderr, "%s: ", argv[0]);
      perror(argv[optind]);
    }
    optind++;
  }
}

void print_file(FILE* file, struct flags FLAG) {
  int symbol, symbol_before = '\n';
  int stroka = 1, null_stroka = 0;
  while ((symbol = fgetc(file)) != EOF) {
    if (FLAG.s == 1 && symbol_before == '\n' && symbol == '\n') {
      null_stroka++;
      if (null_stroka > 1) continue;
    } else {
      null_stroka = 0;
    }
    if (FLAG.n == 1 && symbol_before == '\n') {
      printf("%6d\t", stroka);
      stroka++;
    }
    if (FLAG.b == 1 && symbol_before == '\n' && symbol != '\n') {
      printf("%6d\t", stroka);
      stroka++;
    }
    if (FLAG.e == 1 && symbol == '\n') printf("%c", '$');
    if (FLAG.t == 1 && symbol == '\t') {
      printf("^");
      symbol = 'I';
    }
    if (FLAG.v == 1) {
      if (symbol >= 0 && symbol != 9 && symbol != 10 && symbol < 32) {
        printf("^");
        symbol += 64;
      } else if (symbol == 127) {
        printf("^");
        symbol -= 64;
      } else if (symbol > 127 && symbol < 160) {
        printf("M-^");
        symbol -= 64;
      } else if (symbol >= 160 && symbol < 255) {  // This is only for Ubuntu
        printf("M-");
        symbol -= 128;
      } else if (symbol == 255) {  // This is only for Ubuntu
        printf("M-^");
        symbol = '?';
      }
    }
    printf("%c", symbol);
    symbol_before = symbol;
  }
}
