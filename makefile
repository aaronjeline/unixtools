all: ls cat cp wc pwd tar echo

echo: echo.c
	gcc -g echo.c -o echo.bin -O0

wc: wc.c
	gcc -g wc.c -o wc.bin -O0

ls: ls.c
	gcc -g ls.c -o ls.bin -O0

cat: cat.c
	gcc -g cat.c -o cat.bin -O0

cp: cp.c
	gcc -g cp.c -o cp.bin -O0

pwd: pwd.c
	gcc pwd.c -o pwd.bin -O0

tar: tar.c
	gcc -g tar.c tarHeader.c -o tar.bin -O0

clean:
	rm *.bin

