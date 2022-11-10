#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_file(FILE *file, int number, int number_nonblank, int squeeze_blank,
                int show_ends, int show_nonprinting, int show_tabs);

int main(int argc, char *argv[]) {
  int flag = 0;
  int number = 0;
  int number_nonblank = 0;
  int squeeze_blank = 0;
  int show_ends = 0;
  int show_nonprinting = 0;
  int show_tabs = 0;

  const char *short_options = "beEnstTv";

  const struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {NULL, 0, NULL, 0}};

  opterr = 0;

  while ((flag = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (flag) {
      case 'b':
        number = 1;
        number_nonblank = 1;
        break;
      case 'e':
        show_ends = 1;
        show_nonprinting = 1;
        break;
      case 'E':
        show_ends = 1;
        break;
      case 'n':
        number = 1;
        break;
      case 's':
        squeeze_blank = 1;
        break;
      case 't':
        show_tabs = 1;
        show_nonprinting = 1;
        break;
      case 'T':
        show_tabs = 1;
        break;
      case 'v':
        show_nonprinting = 1;
        break;
      default:
        fprintf(stderr,
                "s21_cat: illegal option\nusage: ./s21_cat [-beEnstTv] [file] "
                "...\n");
        break;
    }
  }

  if (optind >= argc) {
    fprintf(
        stderr,
        "s21_cat: illegal option\nusage: ./s21_cat [-beEnstTv] [file] ...\n");
  }

  if (optind < argc) {
    do {
      char *file_name = argv[optind];
      FILE *file;
      if ((file = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "s21_cat: %s: No such file or directory", file_name);
      } else {
        print_file(file, number, number_nonblank, squeeze_blank, show_ends,
                   show_nonprinting, show_tabs);
        fclose(file);
      }
    } while (++optind < argc);
  }

  return 0;
}

void print_file(FILE *file, int number, int number_nonblank, int squeeze_blank,
                int show_ends, int show_nonprinting, int show_tabs) {
  int size_text = 256;
  char *text = calloc(sizeof(char), size_text);
  char c;
  int iter = 0, number_string = 1;
  while (fscanf(file, "%c", &c) == 1) {
    text[iter] = c;
    if (iter > size_text - 10) {
      size_text *= 2;
      text = (char *)realloc(text, size_text);
    }
    iter++;
  }

  if (number_nonblank == 1) {
    if (0 < iter && text[0] != '\n') fprintf(stdout, "%6d\t", number_string++);// \t
  } else if (number == 1) {
    if (0 < iter) fprintf(stdout, "%6d\t", number_string++);
  }

  for (int i = 0; i < iter; ++i) {
    c = text[i];
    int flag_work_5 = 0;

    if (squeeze_blank == 1) {
      if (i < iter - 2 && c == '\n' && c == text[i + 1] &&
          text[i + 1] == text[i + 2]) {
        continue;
      }
    }

    if (show_nonprinting == 1) {
      if (((int)c >= 0 && (int)c < 32 && c != '\n' && (int)c != 9) ||
          (int)c == 127) {
        if ((int)c != 127) {
          c = (char)((int)c + 64);
        } else
          c = '?';//create error ? -> !
        flag_work_5 = 1;
      }
    }

    if (show_ends == 1) {
      if (c == '\n') {
        fprintf(stdout, "$"); //$
        flag_work_5 = 0;
      }
    }

    if (show_tabs == 1) {
      if (c == (char)9) {
        c = 'I';
        flag_work_5 = 1;
      }
    }

    if (flag_work_5 == 1) {
      fprintf(stdout, "^");
    }
    fprintf(stdout, "%c", c);

    if (number_nonblank == 1) {
      if (i < iter - 1 && c == '\n' && c != text[i + 1])
        fprintf(stdout, "%6d\t", number_string++);
    } else if (number == 1) {
      if (c == '\n' && i < iter - 1) fprintf(stdout, "%6d\t", number_string++);
    }
  }
  free(text);
}