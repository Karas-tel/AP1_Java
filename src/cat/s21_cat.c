#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>

void print_file(FILE *file, int *flags);

int main(int argc, char **argv) {
    int flagc = argc - 1;
    int *flagv = (int*)malloc(flagc * sizeof(int));
    int *flags = (int*)calloc(sizeof(int), 6); // 3 flags: 0 - 's', 1 - 'b', 2 - 'n', 3 - 'E', 4 - 'T', 5 - 'v', 6 - 'e', 7 't'
    for(int i = 0; i < flagc; ++i) {
        if (argv[i + 1][0] == '-') {
            flagv[i] = 1;
            int j = 1;
            while(argv[i + 1][j] != '\0') {
                switch (argv[i + 1][j])
                {
                case 's':
                    flags[0] = 1;
                    break;
                case 'b':
                    flags[1] = 1;
                    break;
                case 'n':
                    flags[2] = 1;
                    break;
                case 'E':
                    flags[3] = 1;
                    break;
                case 'T':
                    flags[4] = 1;
                    break;
                case 'v':
                    flags[5] = 1;
                    break;
                case 'e':
                    flags[5] = 1;
                    flags[3] = 1;
                    break;
                case 't':
                    flags[5] = 1;
                    flags[4] = 1;
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
        if (flagv[i] == 0) { //if flag is name_file
            FILE *fp;
            //char c;
            if ((fp = fopen(argv[i + 1], "r")) == NULL) {
                printf("s21_cat: %s: Нет такого файла или каталога", argv[i + 1]);
            } else {
                print_file(fp, flags);
                // while (fscanf(fp, "%c", &c) == 1) {
                //     fprintf(stdout, "%c", c);
                // }
                fclose(fp);

            }
        }
    }
/*
    printf("\nargc: %d\n", argc);
    for(int i = 1; i < argc; ++i) {
        printf("argv(%d): %s %s a flag\n", i, argv[i], flagv[i - 1] == 1 ? "is" : "isn't");
    }
*/
    free(flagv);
    free(flags);
    return 0;
}

void print_file(FILE *file, int *flags) {
    int size_text = 256;
    char* text = calloc(sizeof(char), size_text);
    char c;
    int iter = 0, number = 1;
    while (fscanf(file, "%c", &c) == 1) {
        text[iter] = c;
        if (iter > size_text - 10) {
            size_text *= 2;
            text = (char *) realloc(text, size_text);
        }
        iter++;
    }
    
    if (flags[1] == 1) {
            if (0 < iter && text[0] != '\n')
                fprintf(stdout, "%6d\t", number++);
        } else if (flags[2] == 1) {
            if (0 < iter)
                fprintf(stdout, "%6d\t", number++);
        }

    for (int i = 0; i < iter; ++i) {
        c = text[i];
        int flag_work_5 = 0;
        if (flags[0] == 1) { // flag -s
            if (i < iter - 2 && c == '\n' && c == text[i+1] && text[i+1] == text[i+2] ) { continue; }
        }

        if (flags[5] == 1) { // -v
            if (((int)c >= 0 && (int)c < 32 && c != '\n' && (int)c != 9) || (int)c == 127) {
                if ((int)c != 127) {
                    c = (char)((int)c + 64);
                } else c = '?';
                flag_work_5 = 1;
            }
        }

        if (flags[3] == 1) { // print $ flag -E
            if (c == '\n') {
                fprintf(stdout, "$");
                flag_work_5 = 0;
            }
        }
        if (flags[4] == 1) { // tab -> ^| flag -T
            if (c == (char)9) {
                c = 'I'; 
                flag_work_5 = 1;
            }
        }
        
        if (flag_work_5 == 1) {
            fprintf(stdout, "^");
        }
        fprintf(stdout, "%c", c);
        if (flags[1] == 1) { // print number not empty strings flag -b
            if (i < iter - 1 && c == '\n' && c != text[i+1])
                fprintf(stdout, "%6d\t", number++);
        } else if (flags[2] == 1) { // print number empty strings flag -n
            if (c == '\n')
                fprintf(stdout, "%6d\t", number++);
        }
    }
    free(text);
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