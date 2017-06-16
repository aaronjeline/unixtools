all: ls cat cp

ls: ls.c
	gcc -g ls.c -o ls.bin

cat: cat.c
	gcc -g cat.c -o cat.bin

cp: cp.c
	gcc -g cp.c -o cp.bin

clean:
	rm *.bin
