FLAGS= -Wall -Wextra -Werror -std=c11

all: s21_cat

s21_cat: s21_cat.c s21_cat.h
	gcc $(FLAGS) s21_cat.c -o s21_cat

clang:
	clang-format -i --style=google *.c *.h *.txt
	cp ../../materials/linters/.clang-format ../cat/.clang-format;

clean:
	rm -f s21_cat log.txt

rebuild: clean all

test: rebuild
	bash s21_test_cat.sh
