CFLAGS = -Wall -Wextra -Werror

all:
	#hello there

s21_cat: cat/s21_cat.c
	gcc $(CFLAGS) cat/s21_cat.c -o cat/s21_cat
	make clean

s21_cat_test: cat/s21_cat_test.c
	gcc $(CFLAGS) cat/s21_cat_test.c -o cat/s21_cat_test
	make clean

s21_grep: s21_grep.o grep_flags.o print_error.o read_file.o
	gcc $(CFLAGS) -o grep/s21_grep s21_grep.o grep_flags.o print_error.o read_file.o
	make clean

s21_grep.o: grep/s21_grep.c
	gcc $(CFLAGS) -c grep/s21_grep.c

grep_flags.o: grep/grep_flags.c
	gcc $(CFLAGS) -c grep/grep_flags.c

print_error.o: grep/print_error.c
	gcc $(CFLAGS) -c grep/print_error.c

read_file.o: grep/read_file.c
	gcc $(CFLAGS) -c grep/read_file.c

s21_grep_test: grep/s21_grep_test.c
	gcc $(CFLAGS) grep/s21_grep_test.c -o grep/s21_grep_test
	make clean

clean:
	rm -f ../cat/*.o
	rm -f *.o

check:
	#cp ../materials/linters/CPPLINT.cfg ./
	#python3 ../materials/linters/cpplint.py --extensions=c *.c
	#python3 ../materials/linters/cpplint.py --extensions=h *.h
	#cppcheck --enable=all --suppress=missingIncludeSystem *.c

git:
	make clean
	git add *.c
	#git add *.h
	git add Makefile
	git commit -m "develop_C3"
	git push origin develop