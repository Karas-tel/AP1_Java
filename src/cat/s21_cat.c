#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int flagc = argc - 1;
    int *flagv = (int*)malloc(flagc * sizeof(int));
    int *flags = (int*)calloc(sizeof(int), 3); // 3 flags: 0 - 'b', 1 - 'n', 2 - 's' 
    for(int i = 0; i < flagc; ++i) {
        if (argv[i + 1][0] == '-') {
            flagv[i] = 1;
            int j = 1;
            while(argv[i + 1][j] != '\0') {
                switch (argv[i + 1][j])
                {
                case 'b':
                    flags[0] = 1;
                    break;
                case 'n':
                    flags[1] = 1;
                    break;
                case 's':
                    flags[2] = 1;
                    break;
                default:
                    flagv[i] = -1;
                    printf("s21_cat: неверный ключ — «%c»\n", argv[i + 1][j]);
                    exit(0);
                    break;
                }
                j++;
            }
        } else {
            flagv[i] = 0;
        }
    }

    for(int i = 0; i < flagc; ++i) {
        if (flagv[i] == 0) {
            FILE *fp;
            char c;
            if ((fp = fopen(argv[i + 1], "r")) == NULL) {
                printf("s21_cat: %s: Нет такого файла или каталога", argv[i + 1]);
            } else {
                while (fscanf(fp, "%c", &c) == 1) {
                    fprintf(stdout, "%c", c);
                }
            }
        }
    }

    printf("argc: %d\n", argc);
    for(int i = 1; i < argc; ++i) {
        printf("argv(%d): %s %s a flag\n", i, argv[i], flagv[i - 1] == 1 ? "is" : "isn't");
    }
    free(flagv);
    free(flags);
    return 0;
}

// int check_flag(char *flag){
//     while(*flag != '\0') {
//         switch (*flag)
//         {
//         case '':
//             /* code */
//             break;
        
//         default:
//             break;
//         }
//     }
//     return 0;
// }