#include "read_file.h"

int get_string(FILE *file, char **string, int *size_string) {
  *size_string = 256;
  *string = calloc(sizeof(char), *size_string);// need check memory
  char ch;
  int iter = 0;
  int correct = 0;
  while ((correct = fscanf(file, "%c", &ch)) == 1 && ch != '\n') {
    (*string)[iter++] = ch;
    if (iter > *size_string - 10) {
      *size_string *= 1.7;
      *string = (char *)realloc(*string, *size_string);// need check memory
    }
  }
  return correct;
}