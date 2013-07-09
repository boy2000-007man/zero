CC = g++
CCFLAGS = -c -g
objects = pretreatment.o infixExpression.o postfixExpression.o main.o

.cpp.o:
	$(CC) $< $(CCFLAGS) -o $@

main: $(objects)
	$(CC) $(objects) -o main

pretreatment.o: pretreatment.h pretreatment.cpp
infixExpression.o: infixExpression.h infixExpression.cpp
postfixExpression.o: postfixExpression.h postfixExpression.cpp
main.o: pretreatment.h infixExpression.h postfixExpression.h main.cpp

.PHONY: clean
clean:
	rm $(objects) main
