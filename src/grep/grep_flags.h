#ifndef SRC_GREP_GREP_FLAGS_H_
#define SRC_GREP_GREP_FLAGS_H_

struct grep_flags {
  int pattern;             // -e [pattern] | <pattern>
  int ignore_case;         // -i | --ignore-case
  int invert_match;        // -v | --invert-match
  int count;               // -c | --count
  int files_with_matches;  // -l | --files-with-matches
  int line_number;         // -n | --line-number
  int no_filename;         // -h | --no-filename
  int no_messages_error;   // -s | --no-messages-error
  int only_matching;       // -o | --only-matching
  int pattern_from_file;   // -f [file] | <pattern-from-file>
  int quantity_files;      // counter files
};

void zeroing_flags(struct grep_flags *flags);
int parse_argv(int argc, char *argv[], struct grep_flags *flags, char **pattern,
               int *size_patt);
int add_pattern(char **pattern, int *size_pattern, char *optarg);
int add_file_pattern(char **pattern, int *size_pattern, char *optarg);
int remove_n(char *pattern);

#endif  // SRC_GREP_GREP_FLAGS_H_