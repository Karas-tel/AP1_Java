#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "print_error.h"

struct grep_flags {
  int pattern;             // [-e] <pattern>
  int ignore_case;         // -i | --ignore-case
  int invert_match;        // -v | --invert-match
  int count;               // -c | --count
  int files_with_matches;  // -l | --files-with-matches
  int line_number;         // -n | --line-number
  int no_filename;         // -h | --no-filename
  int no_messages_error;   // -s | --no-messages-error
  int only_matching;       // -o | --only-matching
  int pattern_from_file;   // -f [file] | <pattern-from-file>
  int many_files;
};

int parse_argv(int argc, char *argv[],
               struct grep_flags *flags, char **pattern);
void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name);
int print_color_string(char *text, int size_text, regmatch_t match);
int get_text(FILE *file, char **text, int *size_text);
void zeroing_flags(struct grep_flags *flags);

int main(int argc, char *argv[]) {
  int size_patt = 250;
  char *pattern = malloc(size_patt * sizeof(char));
  
  regex_t regex;
  int cflags = REG_EXTENDED;
  opterr = 0;

  struct grep_flags flags;
  zeroing_flags(&flags);
  
  parse_argv(argc, &argv, &flags, &pattern);

  if (flags.ignore_case == 1) cflags += REG_ICASE;

  if (optind < argc && (flags.pattern != 0 || flags.pattern_from_file != 0)) {
    do {
      char *file_name = argv[optind];
      FILE *file;
      if ((file = fopen(file_name, "r")) == NULL) {
        print_error(NO_FILE, file_name, flags.no_messages_error);
        //fprintf(stderr, "s21_grep: %s: No such file or directory", file_name);
      } else {
        if (regcomp(&regex, pattern, cflags) == 0) {
          find_in_file(file, flags, regex, file_name);
        }
        fclose(file);
      }
    } while (++optind < argc);
  }
  free(pattern);
  return 0;
}

int parse_argv(int argc, char *argv[], struct grep_flags *flags, char **pattern) {
  int flag = 0;
  (*pattern)[0] = '\0';
  const char *short_options = "e:ivclnhsof:";

  while ((flag = getopt(argc, argv, short_options)) != -1) {
    switch (flag) {
      case 'e':
        (*flags).pattern = 1;
        char buf[500];
        if ((*pattern)[0] != '\0') {
          sprintf(buf, "|%s", optarg);
          strcat((*pattern), buf);
        } else
          sprintf((*pattern), "%s", optarg);
        break;
      case 'i':
        (*flags).ignore_case = 1;
        break;
      case 'v':
        (*flags).invert_match = 1;
        break;
      case 'c':
        (*flags).count = 1;
        break;
      case 'l':
        (*flags).files_with_matches = 1;
        break;
      case 'n':
        (*flags).line_number = 1;
        break;
      case 'h':
        (*flags).no_filename = 1;
        break;
      case 's':
        (*flags).no_messages_error = 1;
        break;
      case 'o':
        (*flags).only_matching = 1;
        break;
      case 'f':
        (*flags).pattern_from_file = 1;
        break;
      default:
        print_error(ILLEGAL_OPTION, NULL, flags->no_messages_error);
        break;
    }
  }

  if (optind >= argc) {
    print_error(NO_OPTION, NULL, flags->no_messages_error);
  }
  (*flags).many_files = argc - optind;
  return 0;
}

void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name) {
  int size_text;
  char *text;
  regmatch_t match;
  int correct = 0;
  int rez_regexec = 0;
  int counter_all = 0;
  int counter_match = 0;
  int counter_no_match = 0;
  //недоделаны обработки флага -l
  do {
    counter_all++;
    correct = get_text(file, &text, &size_text);
    rez_regexec = regexec(&regex, text, 1, &match, REG_NOTEOL);
    if (rez_regexec != REG_NOMATCH &&
        flags.invert_match == 0) {  //если не инвентировано
      counter_match++;
      if (flags.count == 0) {  //если нет вывода только строк
        if (flags.line_number == 1) {  //нумерация строк
          if ((flags.many_files > 1 &&
               (flags.pattern == 1 || flags.pattern_from_file == 1)) ||
              flags.many_files > 2) {
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
  } while (correct == 1);
  //недоделаны обработки флага -l
  //недоделаны обработки флага -l
  if (flags.count == 1) {  //вывод только строк
    if ((flags.many_files > 1 &&
         (flags.pattern == 1 || flags.pattern_from_file == 1)) ||
        flags.many_files > 2) {
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
  free(text);
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

int get_text(FILE *file, char **text, int *size_text) {
  *size_text = 256;
  *text = calloc(sizeof(char), *size_text);
  char ch;
  int iter = 0;
  int correct = 0;
  while ((correct = fscanf(file, "%c", &ch)) == 1 && ch != '\n') {
    (*text)[iter++] = ch;
    if (iter > *size_text - 10) {
      *size_text *= 1.7;
      *text = (char *)realloc(*text, *size_text);
    }
    // iter++;
  }

  // if (correct == 1) {
  //     (*text)[iter++] = '\n';
  //     *size_text = iter;
  // }
  return correct;
}

void zeroing_flags(struct grep_flags *flags) {
  (*flags).pattern = 0;             // [-e] <pattern>
  (*flags).ignore_case = 0;         // -i | --ignore-case
  (*flags).invert_match = 0;        // -v | --invert-match
  (*flags).count = 0;               // -c | --count
  (*flags).files_with_matches = 0;  // -l | --files-with-matches
  (*flags).line_number = 0;         // -n | --line-number
  (*flags).no_filename = 0;         // -h | --no-filename
  (*flags).no_messages_error = 0;   // -s | --no-messages-error
  (*flags).only_matching = 0;       // -o | --only-matching
  (*flags).pattern_from_file = 0;   // -f [file] | <pattern-from-file>
  (*flags).many_files = 0;
}