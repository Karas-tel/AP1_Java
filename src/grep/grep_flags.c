#include "grep_flags.h"
#include "print_error.h"
#include "read_file.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int add_pattern(char **pattern, int *size_pattern, char *optarg) {
    int size_opt = strlen(optarg);
    int size_pat = strlen(*pattern);
    int flag_correct_work = 0;
    if ((size_opt + size_pat + 2) >= *size_pattern) {
        *size_pattern = size_opt * 1.5 + size_pat;
        *pattern = (char *)realloc(*pattern, *size_pattern);
    }
    if (*pattern == NULL) {
        print_error(WRONG_MEMORY, NULL, 0);
        flag_correct_work = -1;
    }
    if (flag_correct_work == 0) {
        if ((*pattern)[0] != '\0' && optarg[0] != '\0')
         strcat(*pattern, "|");
        strcat(*pattern, optarg);
    }
    return flag_correct_work;
}

int add_file_pattern(char **pattern, int *size_pattern, char *optarg, struct grep_flags flags) {
    int flag_correct_work = 0;
    FILE *file;
    if ((file = fopen(optarg, "r")) == NULL) {
        print_error(NO_FILE, optarg, flags.no_messages_error);
        flag_correct_work = -1;
    } else {
        int size_pif;
        char *patt_in_file;
        int end_file = 0;
        do {
            end_file = get_string(file, patt_in_file, size_pif);
            flag_correct_work = add_pattern(pattern, size_pattern, patt_in_file);
        } while (end_file == 1);
        fclose(file);
        free(patt_in_file);///error, wrong free if not malcal
    }
    return flag_correct_work;
}

int parse_argv(int argc, char *argv[],
               struct grep_flags *flags, char **pattern, int *size_patt) {
  int flag_char = 0;
  int flag_correct_work = 0;
  (*pattern)[0] = '\0';
  const char *short_options = "e:ivclnhsof:";

  while ((flag_char = getopt(argc, argv, short_options)) != -1) {
    switch (flag_char) {
      case 'e':
        flags->pattern = 1;
        add_pattern(pattern, size_patt, optarg);
        break;
      case 'i':
        flags->ignore_case = 1;
        break;
      case 'v':
        flags->invert_match = 1;
        break;
      case 'c':
        flags->count = 1;
        break;
      case 'l':
        flags->files_with_matches = 1;
        break;
      case 'n':
        flags->line_number = 1;
        break;
      case 'h':
        flags->no_filename = 1;
        break;
      case 's':
        flags->no_messages_error = 1;
        break;
      case 'o':
        flags->only_matching = 1;
        break;
      case 'f':
        flags->pattern_from_file = 1;
        break;
      default:
        print_error(ILLEGAL_OPTION, NULL, 0);
        break;
    }
  }

  if (optind >= argc) {
    print_error(NO_OPTION, NULL, 0);
    flag_correct_work = -1;
  }
  flags->many_files = argc - optind;
  return flag_correct_work;
}

void zeroing_flags(struct grep_flags *flags) {
  flags->pattern = 0;             
  flags->ignore_case = 0;         
  flags->invert_match = 0;       
  flags->count = 0;             
  flags->files_with_matches = 0;  
  flags->line_number = 0; 
  flags->no_filename = 0;  
  flags->no_messages_error = 0; 
  flags->only_matching = 0; 
  flags->pattern_from_file = 0; 
  flags->many_files = 0;
}