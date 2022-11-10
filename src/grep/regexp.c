#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

struct grep_flags {
    int pattern; // [-e] <pattern>
    int ignore_case; // -i | --ignore-case
    int invert_match; // -v | --invert-match 
    int count; // -c | --count
    int files_with_matches; // -l | --files-with-matches
    int line_number; // -n | --line-number
    int no_filename; // -h | --no-filename
    int no_messages_error; // -s | --no-messages-error
    int only_matching; // -o | --only-matching
    int pattern_from_file; // -f [file] | <pattern-from-file>
};

void find_in_file(FILE* file, struct grep_flags flags, regex_t regex);
int print_string(char *text, int size_text, regmatch_t match, int *iter);
int get_text(FILE* file, char **text, int *size_text);

int main() {
    regex_t regex;
    struct grep_flags flags;
    char* reg = "ag";
    if (regcomp(&regex, reg, REG_EXTENDED) == 0) {
        printf("success\n");
        char *file_name = "test_case_grep.txt";
        FILE *file;
        if ((file = fopen(file_name, "r")) == NULL) {
            fprintf(stderr, "s21_grep: %s: No such file or directory", file_name);
        } else {
            find_in_file(file, flags, regex);
            fclose(file);
        }
    }
    else {
        printf("failure\n");
        return 0; 
    }
    
    printf("\n");
    regfree(&regex);
    return 0;
}

void find_in_file(FILE* file, struct grep_flags flags, regex_t regex) {
    int size_text;
    int iter = 0;
    char *text;
    regmatch_t match;
    get_text(file, &text, &size_text);
    if (regexec(&regex, text, 1, &match, REG_NOTEOL) == REG_NOMATCH) printf("no match\n");
    else print_string(text, size_text, match, &iter);
    
}

int print_string(char *text, int size_text, regmatch_t match, int *iter) {
    for (int i = *iter; i < match.rm_so; ++i ) {
        printf("%c", text[i]);
    }
    printf("\033[0;31m");
    for (int i = match.rm_so; i < match.rm_eo; ++i ) {
        printf("%c", text[i]);
    }
    printf("\033[0m");
    for (int i = match.rm_eo; text[i] != '\n' && i < size_text; ++i, *iter = i ) {
        printf("%c", text[i]);
    }
    return 0;
}

int get_text(FILE* file, char **text, int *size_text) {
    *size_text = 256;
    *text = calloc(sizeof(char), *size_text);
    char ch;
    int iter = 0;
    while (fscanf(file, "%c", &ch) == 1) {
        (*text)[iter] = ch;
        if (iter > *size_text - 10) {
            *size_text *= 1.7;
            *text = (char *)realloc(*text, *size_text);
        }
        iter++;
    }
    *size_text = iter;
    return 0;
}