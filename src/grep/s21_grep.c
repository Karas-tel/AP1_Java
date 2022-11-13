#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "print_error.h"
#include "grep_flags.h"
#include "read_file.h"

void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name);
int print_color_string(char *text, int size_text, regmatch_t match);

int main(int argc, char *argv[]) {
  int size_patt = 250;
  char *pattern = malloc(size_patt * sizeof(char));
  
  regex_t regex;
  int cflags = REG_EXTENDED;
  opterr = 0;

  struct grep_flags flags;
  zeroing_flags(&flags);
  
  parse_argv(argc, argv, &flags, &pattern, &size_patt);

  if (flags.ignore_case == 1) cflags += REG_ICASE;

  if (optind < argc && (flags.pattern != 0 || flags.pattern_from_file != 0)) {
    do {
      char *file_name = argv[optind];
      FILE *file;
      if ((file = fopen(file_name, "r")) == NULL) {
        print_error(NO_FILE, file_name, flags.no_messages_error);
      } else {
        if (regcomp(&regex, pattern, cflags) == 0) {//вынести выше не для повтора
          find_in_file(file, flags, regex, file_name);
        }
        fclose(file);
      }
    } while (++optind < argc);
  }
  free(pattern);
  return 0;
}


void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name) {
  int size_text;
  char *text;
  regmatch_t match;
  errors error = GOOD_WORK;
  int rez_regexec = 0;
  int counter_all = 0;
  int counter_match = 0;
  int counter_no_match = 0;
  //недоделаны обработки флага -l
  do {
    counter_all++;
    error = get_string(file, &text, &size_text);
    rez_regexec = regexec(&regex, text, 1, &match, REG_NOTEOL);
    if (rez_regexec != REG_NOMATCH &&
        flags.invert_match == 0) {  //если не инвентировано
      counter_match++;
      if (flags.count == 0) {  //если нет вывода только строк
        if (flags.line_number == 1) {  //нумерация строк
          if ((flags.quantity_files > 1 &&
               (flags.pattern == 1 || flags.pattern_from_file == 1)) ||
              flags.quantity_files > 2) {
            printf("%s:%d:%s\n", file_name, counter_all, text);
          } else {
            printf("%d:%s\n", counter_all, text);
          }
        } else {
          printf("%s\n", text);
        }
      }
    } else if (rez_regexec == REG_NOMATCH &&
               flags.invert_match == 1) {  //если инвентировано
      counter_no_match++;
      if (flags.count == 0) {  //если нет вывода только строк
        if (flags.line_number == 1) {  //нумерация строк
          printf("%d:%s\n", counter_all, text);
        } else {
          printf("%s\n", text);
        }
      }
    }
  } while (error == GOOD_WORK && error != WRONG_MEMORY);
  //недоделаны обработки флага -l
  //недоделаны обработки флага -l
  if (flags.count == 1) {  //вывод только строк
    if ((flags.quantity_files > 1 &&
         (flags.pattern == 1 || flags.pattern_from_file == 1)) ||
        flags.quantity_files > 2) {
      // printf("%s:%d\n", file_name, counter_match);
      if (flags.invert_match == 0) {
        if (flags.files_with_matches == 0) {
          printf("%s:%d\n", file_name, counter_match);
        } else {
          printf("%s:%d\n", file_name, counter_match);
        }
      } else
        printf("%d\n", counter_no_match);
    }
    if (flags.invert_match == 0) {
      if (flags.files_with_matches == 0) {
        printf("%d\n", counter_match);
      } else {
      }
    } else
      printf("%d\n", counter_no_match);
  }
  // -l
  free(text);///error, wrong free if not malcal
}

int print_color_string(char *text, int size_text, regmatch_t match) {
  int i;
  for (i = 0; i < match.rm_so; ++i) {
    printf("%c", text[i]);
  }
  printf("\033[0;31m");
  for (i = match.rm_so; i < match.rm_eo; ++i) {
    printf("%c", text[i]);
  }
  printf("\033[0m");
  for (i = match.rm_eo; text[i] != '\n' && i < size_text; ++i) {
    printf("%c", text[i]);
  }
  //*iter = match.rm_eo;
  // if (i != size_text) printf("%c", text[i]);
  printf("\n");
  return 0;
}
