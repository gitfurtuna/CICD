#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int result = 0;
  struct flags FLAG = {0};
  if (argc > 2) {
    result = find_flag(argc, argv, &FLAG);
    FLAG.files = argc - optind;
    while (optind < argc) {
      FILE *f = NULL;
      f = fopen(argv[optind], "r");
      if (f) {
        print_file(FLAG, argv[optind], f);
        fclose(f);
      } else {
        if (!FLAG.s) {
          fprintf(stderr, "%s: ", argv[0]);
          perror(argv[optind]);
        }
      }
      optind++;
    }
  }
  return result;
}

int find_flag(int argc, char *argv[], struct flags *FLAG) {
  int flag = 0, result = 0;
  opterr = 0;
  while ((flag = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (flag) {
      case 'e':
        if ((FLAG->e == 0) && (FLAG->f == 0)) {
          strcpy(FLAG->patterns, optarg);
        } else {
          strcat(FLAG->patterns, "|");
          strcat(FLAG->patterns, optarg);
        }
        FLAG->e = 1;
        break;
      case 'i':
        FLAG->i = 1;
        break;
      case 'v':
        FLAG->v = 1;
        break;
      case 'c':
        FLAG->c = 1;
        break;
      case 'l':
        FLAG->l = 1;
        break;
      case 'n':
        FLAG->n = 1;
        break;
      case 'h':
        FLAG->h = 1;
        break;
      case 's':
        FLAG->s = 1;
        break;
      case 'f':;
        FILE *file = NULL;
        file = fopen(optarg, "r");
        if (file != NULL) {
          char *line = NULL;
          size_t size = 0;
          while (getline(&line, &size, file) != -1) {
            if (line[strlen(line) - 1] == '\n') {
              line[strlen(line) - 1] = '\0';
            }
            if ((FLAG->e == 0) && (FLAG->f == 0)) {
              strcpy(FLAG->patterns, line);
            } else {
              strcat(FLAG->patterns, "|");
              strcat(FLAG->patterns, line);
            }
            FLAG->f = 1;
          }
          free(line);
          fclose(file);
        } else {
          if (!FLAG->s) {
            fprintf(stderr, "%s: ", argv[0]);
            perror(argv[optind - 1]);
          }
          result = 1;
        }
        break;
      case 'o':
        FLAG->o = 1;
        break;
      default:
        fprintf(stderr, "%s: invalid option -- %c\n", argv[0], optopt);
        result = 1;
        break;
    }
  }
  if (!(FLAG->e) && !(FLAG->f)) {
    strcpy(FLAG->patterns, argv[optind]);
    optind++;
  }
  return result;
}

void print_file(struct flags FLAG, char *file_name, FILE *file) {
  char *line = NULL;
  size_t size = 0;
  int code = REG_EXTENDED;
  int x = 0;
  regex_t regs;
  regmatch_t pm[1];

  if (FLAG.i) code = code | REG_ICASE;

  x = regcomp(&regs, FLAG.patterns, code);
  if (x > 0) {
    char errbuf[1024];
    regerror(x, &regs, errbuf, 1024);
    fprintf(stderr, "%s\n", errbuf);
  } else {
    int line_number = 0;
    int count_match = 0;
    while (getline(&line, &size, file) != -1) {
      int match = 0;
      line_number++;
      x = regexec(&regs, line, 1, pm, 0);
      if (x == FLAG.v) {
        match = 1;
        count_match++;
      }
      if (!FLAG.l && !FLAG.c) {
        if (match && FLAG.files > 1 && !FLAG.h) {
          printf("%s:", file_name);
        }
        if (match && FLAG.n) {
          printf("%d:", line_number);
        }
        if (match && !FLAG.o) {
          printf("%s", line);
          if (line[strlen(line) - 1] != '\n') {
            printf("\n");
          }
        }
        if (match && FLAG.o) {
          int step = 0;
          while (regexec(&regs, line + step, 1, pm, 0) == 0) {
            char *buff =
                strndup(line + step + pm[0].rm_so, pm[0].rm_eo - pm[0].rm_so);
            printf("%s", buff);
            if (buff[strlen(buff) - 1] != '\n') {
              printf("\n");
            }
            free(buff);
            step = step + pm[0].rm_eo;
          }
        }
      }
    }
    free(line);
    regfree(&regs);
    if (FLAG.c) {
      if (FLAG.files > 1 && !FLAG.h) {
        printf("%s:", file_name);
      }
      if (FLAG.l && count_match > 0) {
        count_match = 1;
      }
      printf("%d\n", count_match);
    }
    if (FLAG.l && count_match > 0) {
      printf("%s\n", file_name);
    }
  }
}
