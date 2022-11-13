#include "read_file.h"
#include "print_error.h"
#include <stdlib.h>

int get_string(FILE *file, char **string, int *size_string) {
  *size_string = 256;
  *string = calloc(sizeof(char), *size_string);// need check memory
  char ch;
  int iter = 0;
  int correct = 0;
  errors error = GOOD_WORK;
  while ((correct = fscanf(file, "%c", &ch)) == 1 && ch != '\n'
        && error != WRONG_MEMORY) {
    (*string)[iter++] = ch;
    if (iter > *size_string - 10) {
      *size_string *= 1.7;
      char *tmp = (char *)realloc(*string, *size_string);
      if (tmp == NULL) error = WRONG_MEMORY;
      else *string = tmp;
    }
  }
  if (error != WRONG_MEMORY) error = correct == 1 ? GOOD_WORK : END_FILE;
  return error;
}