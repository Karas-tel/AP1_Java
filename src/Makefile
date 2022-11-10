CFLAGS = -Wall -Wextra -Werror

all:
	#hello there

s21_cat: cat/s21_cat.c
	gcc $(CFLAGS) cat/s21_cat.c -o cat/s21_cat
	make clean

s21_cat_test: cat/s21_cat_test.c
	gcc $(CFLAGS) cat/s21_cat_test.c -o cat/s21_cat_test
	make clean

s21_grep: grep/s21_grep.c
	gcc $(CFLAGS) grep/s21_grep.c -o grep/s21_grep
	make clean

s21_grep_test: grep/s21_grep_test.c
	gcc $(CFLAGS) grep/s21_grep_test.c -o grep/s21_grep_test
	make clean

clean:
	rm -f ../cat/*.o

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