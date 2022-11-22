CFLAGS = -Wall -Wextra -Werror

all:
	#hello there

s21_grep: s21_grep.o grep_flags.o print_error.o read_file.o
	gcc $(CFLAGS) -o s21_grep s21_grep.o grep_flags.o print_error.o read_file.o
	make clean

s21_grep.o: s21_grep.c
	gcc $(CFLAGS) -c s21_grep.c

grep_flags.o: grep_flags.c
	gcc $(CFLAGS) -c grep_flags.c

print_error.o: print_error.c
	gcc $(CFLAGS) -c print_error.c

read_file.o: read_file.c
	gcc $(CFLAGS) -c read_file.c

clean:
	rm -f *.o

check:
	make s21_grep
	bash s21_grep_test.sh

git:
	make clean
	git add *.c
	git add *.h
	git add Makefile
	git commit -m "develop_C3"
	git push origin develop