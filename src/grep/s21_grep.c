#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_file(FILE *file, int number, int number_nonblank, int squeeze_blank,
                int show_ends, int show_nonprinting, int show_tabs);

int main(int argc, char *argv[]) {
  int flag = 0;
  int pattern = 0; // [-e] <pattern>
  int ignore_case = 0; // -i | --ignore-case
  int invert_match = 0; // -v | --invert-match 
  int count = 0; // -c | --count
  int files_with_matches = 0; // -l | --files-with-matches
  int line_number = 0; // -n | --line-number
  int no_filename = 0; // -h | --no-filename
  int no_messages_error = 0; // -s | --no-messages-error
  int only_matching = 0; // -o | --only-matching
  int pattern_from_file = 0; // -f [file] | <pattern-from-file>

  const char *short_options = "e:ivclnhsof:";

  opterr = 0;

  while ((flag = getopt(argc, argv, short_options)) != -1) {
    switch (flag) {
      case 'e':
        
        break;
      case 'i':
        ignore_case = 1;
        break;
      case 'v':
        invert_match = 1;
        break;
      case 'c':
        count = 1;
        break;
      case 'l':
        files_with_matches = 1;
        break;
      case 'n':
        line_number = 1;
        break;
      case 'h':
        no_filename = 1;
        break;
      case 's':
        no_messages_error = 1;
        break;
      case 'o':
        only_matching = 1;
        break;
      case 'f':
        
        break;
      default:
        fprintf(stderr,
                "s21_grep: illegal option\nusage: ./s21_grep [-e:ivclnhsof:] [file] "
                "...\n");
        break;
    }
  }

  if (optind >= argc) {
    fprintf(stderr,
                "s21_grep: illegal option\nusage: ./s21_grep [-e:ivclnhsof:] [file] "
                "...\n");
  }

  if (optind < argc) {
    do {
      char *file_name = argv[optind];
      FILE *file;
      if ((file = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "s21_grep: %s: No such file or directory", file_name);
      } else {
        
        fclose(file);
      }
    } while (++optind < argc);
  }

  return 0;
}