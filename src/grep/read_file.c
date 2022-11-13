#include "read_file.h"
#include "print_error.h"
#include <stdlib.h>
#include <string.h>

int get_string(FILE *file, char **string, int *size_string) {
  char ch;
  int iter = 0;
  int correct = 0;
  errors error = GOOD_WORK;
  //print_error(error, "in get_string", 0);
  while ((correct = fscanf(file, "%c", &ch)) == 1 && ch != '\n'
        && error != WRONG_MEMORY) {
    (*string)[iter++] = ch;
    (*string)[iter] = '\0';
    if (iter > *size_string - 10) {
      *size_string *= 1.7;
      char **tmp = (char **)realloc(*string, *size_string);
      if (tmp == NULL) error = WRONG_MEMORY;
      else {
        //*tmp[0] = '\0';
        //strcpy(*tmp, *string);
        string = tmp;
      }
    }
  }
  if (error != WRONG_MEMORY) {
    error = correct == 1 ? GOOD_WORK : END_FILE;
    //print_error(error, "in if error", 0);
    //(*string)[iter] = '\0';
  }
  return error;
}