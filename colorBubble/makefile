colorBubble.exe:main.o color.o
	gcc main.o color.o -o colorBubble.exe
main.o:main.c color.h
	gcc -c main.c -o main.o
color.o:color.c color.h
	gcc -c color.c -o color.o
.PHONY:clean
clean:
	del colorBubble.exe main.o color.o
