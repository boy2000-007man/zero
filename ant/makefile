CC = g++
CCFLAGS = -c -g
objects = sdk.o main.o

.cpp.o:
	$(CC) $< $(CCFLAGS) -o $@

main: $(objects)
	$(CC) $(objects) -o main

sdk.o: sdk.h sdk.cpp
main.o: sdk.h main.cpp

.PHONY: clean
clean:
	rm $(objects) main
