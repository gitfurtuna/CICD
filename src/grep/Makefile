FLAGS= -Wall -Wextra -Werror -std=c11

all: s21_grep

s21_grep: s21_grep.c s21_grep.h
	gcc $(FLAGS) s21_grep.c -o s21_grep

clang:
	clang-format -i --style=google *.c *.h *.txt
	cp ../../materials/linters/.clang-format ../grep/.clang-format;

clean:
	rm -f s21_grep log.txt

rebuild: clean all

test: rebuild
	bash testGrep.sh
