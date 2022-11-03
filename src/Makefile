CFLAGS = -Wall -Wextra -Werror

all:
	#hello there

s21_cat: cat/s21_cat.c
	gcc $(CFLAGS) cat/s21_cat.c -o cat/s21_cat
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