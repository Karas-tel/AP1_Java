#include <regex.h>
#include <stdio.h>

int main() {
    int length = 5;
    regex_t regex;
    regmatch_t match[length];
    char* text = "blacb\nlagrr\n";
    char* text2 = "blacblagrr";
    char* reg = "ag";
    if (regcomp(&regex, reg, REG_EXTENDED | REG_ICASE) == 0) printf("sucsec\n");
    else {
        printf("fail\n");
        return 0; 
    }
    //regexec(&regex, text, length, match, 0); 're'
    int rez;
    rez = regexec(&regex, text, length, match, REG_NOTEOL);
    if (rez == REG_NOMATCH) printf("no match\n");
    else {
        for (int i = 0; i < length ; i++) {
            printf("\"%s\" matches characters %d - %d\n", reg, match[i].rm_so, match[i].rm_eo);
        }
    }
    for (int i = 0; i < match[0].rm_so; ++i ) {
        printf("%c", text[i]);
    }
    printf("\033[0;31m");
    for (int i = match[0].rm_so; i < match[0].rm_eo; ++i ) {
        printf("%c", text[i]);
    }
    printf("\033[0m");
    for (int i = match[0].rm_eo; text[i] != '\0'; ++i ) {
        printf("%c", text[i]);
    }
    //regex exp("(\\b\\S*\\b)");
    //smatch res;
    //string str = "first second third forth";
    //regex_search();
    printf("\n");
    regfree(&regex);
    return 0;
}
//&& match[i].rm_so != -1