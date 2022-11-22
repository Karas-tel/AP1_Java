#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare();
// success and failure
int main() {
  int n = 7;
  int counter = 0;
  int success = 0, failure = 0;
  char flags[8][3] = {{"-i"}, {"-v"}, {"-c"}, {"-l"},
                      {"-n"}, {"-h"}, {"-s"}, {"-o"}};
  char files[4][25] = {{"file_1"}, {"file_2"}, {"file_3"}, {"file_4"}};
  char flags_wp[2][3] = {{"-e"}, {"-e"}};
  char string_f[200];
  char string_greap[300];
  char string_greap_cat[300];
  for (int i1 = 0; i1 < 8; ++i1) {            // 7
    for (int i2 = 0; i2 < 8; ++i2) {          // 7
      for (int i3 = 0; i3 < 4; ++i3) {        // 4
        for (int i4 = 0; i4 < 4; ++i4) {      // 4
          for (int i5 = 0; i5 < 2; ++i5) {    // 2
            for (int i6 = 0; i6 < 2; ++i6) {  // 2
              string_f[0] = '\0';
              string_greap[0] = '\0';
              string_greap_cat[0] = '\0';
              counter++;
              sprintf(string_f, "%s %s %s %s %s %s %s", flags[i1], flags[i2],
                      flags_wp[i5], files[i3], files[i4], flags_wp[i6],
                      files[i4]);
              if (string_f[1] == '\0') string_f[0] = '\0';
              sprintf(string_greap, "grep %s > grep_out_log.txt", string_f);
              sprintf(string_greap_cat, "./s21_grep %s > s21_grep_out_log.txt",
                      string_f);
              system(string_greap);
              system(string_greap_cat);
              int rez = compare();
              if (rez > 0) {
                success++;
              } else if (rez < 0) {
                failure++;
              }
              // if (counter % 1000 == 0)
              printf("\tcounter:%10d\tsuccess:%10d\tfailure:%10d\n", counter,
                     success, failure);
              if (rez < 0) printf("\tcommand: %s\n", string_greap_cat);
            }
          }
        }
      }
    }
  }
  printf("\tcounter:%10d\tsuccess:%10d\tfailure:%10d\n", counter, success,
         failure);
  return 0;
}

int compare() {
  int ch1 = 0, ch2 = 0;
  int rez = 0;

  FILE *f1 = fopen("grep_out_log.txt", "r");      // assert(f1);
  FILE *f2 = fopen("s21_grep_out_log.txt", "r");  // assert(f2);

  while (!feof(f1) && !feof(f2) && (ch1 == ch2)) {
    ch1 = fgetc(f1);
    ch2 = fgetc(f2);
  }

  if (ch1 == ch2)
    rez = 1;
  else
    rez = -1;

  fclose(f2);
  fclose(f1);
  system("rm grep_out_log.txt s21_grep_out_log.txt");
  return rez;
}