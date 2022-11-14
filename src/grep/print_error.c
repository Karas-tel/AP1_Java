#include "print_error.h"
#include <stdio.h>

void print_error(errors error, char* content, int no_message) {
    if (no_message == 0) {
        switch (error)
        {
        case NO_FILE:
            fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                content != NULL ? content : "");
            break;
        case NO_OPTION:
            fprintf(stderr, "s21_grep: illegal option\nusage: ./s21_grep "
                "[-e:ivclnhsof:] "
                "[file] "
                "...\n");
            break;
        case ILLEGAL_OPTION:
            fprintf(stderr, "s21_grep: illegal option\nusage: ./s21_grep "
                "[-e:ivclnhsof:] "
                "[file] "
                "...\n");
            break;
        case WRONG_PATTERN:
            fprintf(stderr, "s21_grep: %s: Wrong regular pattern\n",
                content != NULL ? content : "");
            break; 
        case WRONG_MEMORY:
            fprintf(stderr, "s21_grep: Wrong memory\n");
            break;
        /*
        case GOOD_WORK:
            fprintf(stderr, "s21_grep: %s: GoodWork\n", content != NULL ? content : "");
            break;  
        case END_FILE:
            fprintf(stderr, "s21_grep: %s: EndFile\n", content != NULL ? content : "");
            break;  
        */
        default:
            break;
        }
    }
}