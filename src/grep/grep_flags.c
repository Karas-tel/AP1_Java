#include "grep_flags.h"
#include "print_error.h"
#include "read_file.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int add_pattern(char **pattern, int *size_pattern, char *optarg) {
    int size_opt = strlen(optarg);//safe?
    int size_pat = strlen(*pattern);
    errors error = GOOD_WORK;
    if ((size_opt + size_pat + 2) >= *size_pattern) {
        *size_pattern = size_opt * 1.5 + size_pat;
        char *tmp = (char *)realloc(*pattern, *size_pattern);
        if (tmp == NULL) error = WRONG_MEMORY;
        else {
            *pattern = tmp;
            if ((*pattern)[0] != '\0' && optarg[0] != '\0')
                strcat(*pattern, "|");
            strcat(*pattern, optarg);
        }
    }
    return error;
}

int add_file_pattern(char **pattern, int *size_pattern, char *optarg) {
    errors error = GOOD_WORK;
    FILE *file;
    if ((file = fopen(optarg, "r")) == NULL)
        error = NO_FILE;
    else {
        int size_pif = 256;
        char *patt_in_file;
        char *tmp = calloc(sizeof(char), size_pif);
        if (tmp == NULL) error = WRONG_MEMORY;
        else {
            patt_in_file = tmp;
            while (error == GOOD_WORK) {
                error = get_string(file, &patt_in_file, &size_pif);
                if (error  != WRONG_MEMORY)
                    if (add_pattern(pattern, size_pattern, patt_in_file) == WRONG_MEMORY)
                      error = WRONG_MEMORY;//need checker
            }
            free(patt_in_file);
        }
        fclose(file);
    }
    return error == END_FILE ? GOOD_WORK : error;
}

int parse_argv(int argc, char *argv[],
               struct grep_flags *flags, char **pattern, int *size_patt) {
  errors error = GOOD_WORK;
  int flag_char = 0;
  (*pattern)[0] = '\0';
  const char *short_options = "e:ivclnhsof:";

  while ((flag_char = getopt(argc, argv, short_options)) != -1
        && error != WRONG_MEMORY) {
    switch (flag_char) {
      case 'e':
        flags->pattern = 1;
        error = add_pattern(pattern, size_patt, optarg);
        print_error(error, optarg, 0);
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
        error = add_file_pattern(pattern, size_patt, optarg);
        print_error(error, optarg, flags->no_messages_error);
        break;
      default:
        error = ILLEGAL_OPTION;
        print_error(error, NULL, 0);
        break;
    }
  }

  if (optind >= argc) {
    error = NO_OPTION;
    print_error(error, NULL, 0);
  }
  flags->quantity_files = argc - optind;
  return error;
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
  flags->quantity_files = 0;
}