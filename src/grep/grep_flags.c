#include "grep_flags.h"
#include "print_error.h"

#include <getopt.h>
#include <stdlib.h>

int parse_argv(int argc, char *argv[],
               struct grep_flags *flags, char **pattern) {
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
        print_error(ILLEGAL_OPTION, NULL, flags->no_messages_error);
        break;
    }
  }

  if (optind >= argc) {
    print_error(NO_OPTION, NULL, flags->no_messages_error);
  }
  flags->many_files = argc - optind;
  return 0;
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