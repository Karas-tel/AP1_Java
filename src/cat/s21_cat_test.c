#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare();

int main() {
    int n = 12;
    int counter = 0;
    int sucses = 0, fail = 0;
    char flags[12][17] = { {"-b"}, {"-e"}, {"-E"}, {"-n"}, {"-s"}, {"-t"},
                           {"-T"}, {"-v"}, {"--number-nonblank"}, {"--number"},
                           {"squeeze-blank"}, {""} };
    char string[300];
    for (int i1 = 0; i1 < n; ++i1) {
        for (int i2 = 0; i2 < n; ++i2) {
            for (int i3 = 0; i3 < n; ++i3) {
                for (int i4 = 0; i4 < n; ++i4) {
                    for (int i5 = 0; i5 < n; ++i5) {
                        for (int i6 = 0; i6 < n; ++i6) {
                            for (int i7 = 0; i7 < n; ++i7) {
                                for (int i8 = 0; i8 < n; ++i8) {
                                    for (int i9 = 0; i9 < n; ++i9) {
                                        for (int i10 = 0; i10 < n; ++i10) {
                                            for (int i11 = 0; i11 < n; ++i11) {
                                                for (int i12 = 0; i12 < n; ++i12) {
                                                    string[0] = '\0';
                                                    strcat(string, flags[i1]);
                                                    strcat(string, flags[i2]);
                                                    strcat(string, flags[i3]);
                                                    strcat(string, flags[i4]);
                                                    strcat(string, flags[i5]);
                                                    strcat(string, flags[i6]);
                                                    strcat(string, flags[i7]);
                                                    strcat(string, flags[i8]);
                                                    strcat(string, flags[i9]);
                                                    strcat(string, flags[i10]);
                                                    strcat(string, flags[i11]);
                                                    strcat(string, flags[i12]);
                                                    counter++;
                                                    if (counter % 1000 == 0) printf("\tcounter:%18d\tsucses:%18d\tfail:%18d\n", counter, sucses, fail);
                                                    system("cat -n test_case_cat.txt > cat_out_log.txt");
                                                    system("cat/s21_cat -n test_case_cat.txt > s21_cat_out_log.txt");
                                                    if (compare() > 0) {sucses++;}
                                                    else if (compare() < 0) {fail++;}
                                                } 
                                            }
                                        }
                                    } 
                                } 
                            } 
                        } 
                    } 
                }
            }
        } 
    }

    return 0;
}

int compare() {
    int ch1 = 0, ch2 = 0;
   int rez = 0;
 
   FILE* f1 = fopen("cat_out_log.txt", "r"); //assert(f1);
   FILE* f2 = fopen("s21_cat_out_log.txt", "r"); //assert(f2);
 
   while (!feof(f1) && !feof(f2) && (ch1 == ch2))
   {
      ch1 = fgetc(f1);
      ch2 = fgetc(f2);
   }
 
   if (ch1 == ch2)
   {
      rez = 1;
   }
   else
   {
      rez = -1;
   }
 
   fclose(f2);
   fclose(f1);
   return rez;
}