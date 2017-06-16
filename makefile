ls: ls.c
	gcc -g ls.c -o ls.bin

clean:
	rm *.bin
