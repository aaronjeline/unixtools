all: ls cat

ls: ls.c
	gcc -g ls.c -o ls.bin

cat: cat.c
	gcc -g cat.c -o cat.bin

clean:
	rm *.bin
