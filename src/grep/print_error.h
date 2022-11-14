#ifndef SRC_GREP_PRINT_ERROR_H_
#define SRC_GREP_PRINT_ERROR_H_

typedef enum {
  NO_FILE,
  NO_OPTION,
  ILLEGAL_OPTION,
  WRONG_PATTERN,
  WRONG_MEMORY,
  END_FILE,
  GOOD_WORK
} errors;

void print_error(errors error, char *content, int no_message);

#endif  // SRC_GREP_PRINT_ERROR_H_
