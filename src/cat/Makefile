CFLAGS = -Wall -Wextra -Werror

all:
	#hello there

s21_cat: s21_cat.c
	gcc $(CFLAGS) s21_cat.c -o s21_cat
	make clean

s21_cat_test: s21_cat_test.c
	gcc $(CFLAGS) s21_cat_test.c -o s21_cat_test
	make clean

clean:
	rm -f *.o

check:
	make s21_cat
	bash ./s21_cat_test.sh

git:
	make clean
	git add *.c
	#git add *.h
	git add Makefile
	git commit -m "develop_C3"
	git push origin develop