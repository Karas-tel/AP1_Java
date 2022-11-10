#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare();
//success and failure
int main() {
    int n = 7;
    int counter = 0;
    int success = 0, failure = 0;
    char flags[7][2]= { {"b"}, {"e"}, {"n"}, {"s"}, {"t"},
                           {"v"}, {""} };
    char string_f[20];
    char string_cat[300];
    char string_s21_cat[300];
    for (int i1 = 0; i1 < n; ++i1) {
        for (int i2 = 0; i2 < n; ++i2) {
            for (int i3 = 0; i3 < n; ++i3) {
                for (int i4 = 0; i4 < n; ++i4) {
                    for (int i5 = 0; i5 < n; ++i5) {
                        for (int i6 = 0; i6 < n; ++i6) {
                            for (int i7 = 0; i7 < n; ++i7) {
                                string_f[0] = '\0';
                                string_cat[0] = '\0';
                                string_s21_cat[0] = '\0';
                                counter++;
                                sprintf(string_f, "-%s%s%s%s%s%s%s", flags[i1], flags[i2],
                                        flags[i3], flags[i4], flags[i5], flags[i6], flags[i7]);
                                if (string_f[1] == '\0') string_f[0] = '\0';
                                sprintf(string_cat, "cat %s test_case_cat.txt > cat_out_log.txt", string_f);
                                sprintf(string_s21_cat, "./s21_cat %s test_case_cat.txt > s21_cat_out_log.txt", string_f);
                                system(string_cat);
                                system(string_s21_cat);
                                int rez = compare();
                                if (rez > 0) {success++;}
                                else if (rez < 0) {failure++;}
                                if (counter % 1000 == 0) printf("\tcounter:%10d\tsuccess:%10d\tfailure:%10d\n", counter, success, failure);
                            }                                          
                        } 
                    } 
                }
            }
        } 
    }
    printf("\tcounter:%10d\tsuccess:%10d\tfailure:%10d\n", counter, success, failure);
    return 0;
}

int compare() {
    int ch1 = 0, ch2 = 0;
    int rez = 0;

    FILE* f1 = fopen("cat_out_log.txt", "r"); //assert(f1);
    FILE* f2 = fopen("s21_cat_out_log.txt", "r"); //assert(f2);
 
    while (!feof(f1) && !feof(f2) && (ch1 == ch2)) {
        ch1 = fgetc(f1);
        ch2 = fgetc(f2);
    }

    if (ch1 == ch2) rez = 1;
    else rez = -1;
 
    fclose(f2);
    fclose(f1);
    system("rm cat_out_log.txt s21_cat_out_log.txt");
    return rez;
}