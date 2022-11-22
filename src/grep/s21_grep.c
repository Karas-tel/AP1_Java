#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "grep_flags.h"
#include "print_error.h"
#include "read_file.h"

int find_files_with_match(FILE *file, struct grep_flags flags, regex_t regex);
void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name);
void print_match(char *text, int size_text, regmatch_t match,
                 struct grep_flags flags);

int main(int argc, char *argv[]) {
  errors error = GOOD_WORK;

  int size_patt = 256;
  char *pattern = calloc(size_patt, sizeof(char));  // need check memory

  regex_t regex;
  int cflags = REG_EXTENDED;
  opterr = 0;

  struct grep_flags flags;
  zeroing_flags(&flags);

  error = parse_argv(argc, argv, &flags, &pattern, &size_patt);

  if (flags.ignore_case == 1) cflags += REG_ICASE;

  if (flags.pattern == 0 && flags.pattern_from_file == 0 &&
      (error != ILLEGAL_OPTION && error != NO_OPTION)) {
    add_pattern(&pattern, &size_patt, argv[optind++]);
    flags.quantity_files--;
  }

  if (optind < argc && (error != ILLEGAL_OPTION || error != NO_OPTION)) {
    if (regcomp(&regex, pattern, cflags) == 0) {
      do {
        char *file_name = argv[optind];
        FILE *file;
        if ((file = fopen(file_name, "r")) == NULL) {
          print_error(NO_FILE, file_name, flags.no_messages_error);
        } else {
          if (flags.files_with_matches == 1) {
            int rez = find_files_with_match(file, flags, regex);
            if (flags.count == 1) find_in_file(file, flags, regex, file_name);
            if (rez == 1) printf("%s\n", file_name);
          } else {
            find_in_file(file, flags, regex, file_name);
          }
          fclose(file);
        }
      } while (++optind < argc);
      regfree(&regex);
    } else
      print_error(WRONG_PATTERN, pattern, 0);
  } else {
    print_error(NO_OPTION, NULL, 0);
  }
  
  free(pattern);
  return 0;
}

int find_files_with_match(FILE *file, struct grep_flags flags, regex_t regex) {
  errors error = GOOD_WORK;
  int size_text = 256;

  char *text = calloc(size_text, sizeof(char));  // need check memory

  int rez_regexec = 0;
  int exit = 0;
  do {
    text[0] = '\0';
    error = get_string(file, &text, &size_text);
    if (text[0] == '\0') {
      continue;
    }
    rez_regexec = regexec(&regex, text, 0, 0, 0);
    if (rez_regexec != REG_NOMATCH && flags.invert_match == 0) {
      // printf("%s\n", file_name);
      exit = 1;
    }
    if (rez_regexec == REG_NOMATCH && flags.invert_match == 1) {
      // printf("%s\n", file_name);
      exit = 1;
    }
  } while (error == GOOD_WORK && error != WRONG_MEMORY && exit == 0);
  free(text);
  return exit;
}

void find_in_file(FILE *file, struct grep_flags flags, regex_t regex,
                  char *file_name) {
  int size_text = 256;

  char *text = calloc(size_text, sizeof(char));  // need check memory

  regmatch_t match;
  errors error = GOOD_WORK;
  int rez_regexec = 0;
  int counter_all = 0;
  int counter_match = 0;

  do {
    counter_all++;
    text[0] = '\0';
    error = get_string(file, &text, &size_text);  // checker?
    if (text[0] == '\0') {
      continue;
    }
    rez_regexec = regexec(&regex, text, 1, &match, 0);
    if (rez_regexec != REG_NOMATCH && flags.invert_match == 0) {
      counter_match++;
      if (flags.count == 0) {
        if (flags.quantity_files > 1 && flags.no_filename == 0)
          printf("%s:", file_name);
        if (flags.line_number == 1) printf("%d:", counter_all);
        print_match(text, size_text, match, flags);
      }
    }
    if (rez_regexec == REG_NOMATCH && flags.invert_match == 1) {
      counter_match++;
      if (flags.count == 0) {
        if (flags.quantity_files > 1 && flags.no_filename == 0)
          printf("%s:", file_name);
        if (flags.line_number == 1) printf("%d:", counter_all);
        match.rm_eo = size_text;
        match.rm_so = 0;
        print_match(text, size_text, match, flags);
      }
    }
  } while (error == GOOD_WORK);

  if (flags.count == 1) {
    if (flags.quantity_files > 1 && flags.no_filename == 0)
      printf("%s:", file_name);
    printf("%d\n", counter_match);
  }

  free(text);
}

void print_match(char *text, int size_text, regmatch_t match,
                 struct grep_flags flags) {
  int i;
  for (i = 0; i < match.rm_so && flags.only_matching == 0;) {
    printf("%c", text[i++]);
  }
  for (i = match.rm_so;
       i < match.rm_eo && text[i] != '\n' && text[i] != '\0';) {
    printf("%c", text[i++]);
  }
  for (i = match.rm_eo; flags.only_matching == 0 && i < size_text &&
                        text[i] != '\n' && text[i] != '\0';) {
    printf("%c", text[i++]);
  }
  printf("\n");
}
