main:
	clang -Wall --pedantic -g main.c -O3 -o shredder

clean:
	rm shredder