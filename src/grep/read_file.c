#include "read_file.h"

#include <stdlib.h>
#include <string.h>

#include "print_error.h"

int get_string(FILE *file, char **string, int *size_string) {
  char ch;
  int iter = 0;
  int correct = 0;
  errors error = GOOD_WORK;

  while ((correct = fscanf(file, "%c", &ch)) == 1 && ch != '\n' &&
         error != WRONG_MEMORY) {
    (*string)[iter++] = ch;
    (*string)[iter] = '\0';
    if (iter > (*size_string - 10)) {
      *size_string *= 1.7;
      char *tmp = (char *)realloc(*string, *size_string * sizeof(char));
      if (tmp == NULL)
        error = WRONG_MEMORY;
      else
        *string = tmp;
    }
  }

  if (error != WRONG_MEMORY) error = correct == 1 ? GOOD_WORK : END_FILE;

  (*string)[iter] = '\n';

  if (error == END_FILE) (*string)[iter] = '\0';
  (*string)[++iter] = '\0';

  return error;
}