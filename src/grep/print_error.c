#include "print_error.h"

#include <stdio.h>

void print_error(errors error, char *content, int no_message) {
  if (no_message == 0) {
    switch (error) {
      case NO_FILE:
#ifdef __APPLE__
        fprintf(stderr, "grep: %s: No such file or directory\n",
                content != NULL ? content : "");
#elif __linux__
        fprintf(stderr, "grep: %s: Нет такого файла или каталога\n",
                content != NULL ? content : "");
#endif
        break;
      case NO_OPTION:
#ifdef __APPLE__
        fprintf(stderr,
                "usage: grep "
                "[-e:ivclnhsof:] "
                "[file] "
                "...\n");
#elif __linux__
        fprintf(stderr,
                "Использование: grep "
                "[ПАРАМЕТР]… ШАБЛОНЫ [ФАЙЛ]…\n"
                "Запустите «grep --help» для получения более подробного "
                "описания.\n");
#endif
        break;
      case ILLEGAL_OPTION:
#ifdef __APPLE__
        fprintf(stderr,
                "grep: illegal option\nusage: grep "
                "[-e:ivclnhsof:] "
                "[file] "
                "...\n");
#elif __linux__
        fprintf(stderr,
                "grep: неверный ключ\nИспользование: grep "
                "[ПАРАМЕТР]… ШАБЛОНЫ [ФАЙЛ]…\n"
                "Запустите «grep --help» для получения более подробного "
                "описания.\n");
#endif
        break;
      case WRONG_PATTERN:
#ifdef __APPLE__
        fprintf(stderr, "grep: %s: Wrong regular pattern\n",
                content != NULL ? content : "");
#elif __linux__
        fprintf(stderr, "grep: Неверное регулярное выражение\n");
#endif
        break;
      case WRONG_MEMORY:
        fprintf(stderr, "grep: Wrong memory\n");
        break;
      /*
      case GOOD_WORK:
          fprintf(stderr, "s21_grep: %s: GoodWork\n", content != NULL ? content
      :
      ""); break; case END_FILE: fprintf(stderr, "s21_grep: %s: EndFile\n",
      content != NULL ? content : ""); break;
      */
      default:
        break;
    }
  }
}