MODULE_SRC= example_7.cpp
MODULE_OBJ= example_7.o
MODULE_TARGET= example_7
MODULE_INCS= -I..
CCFLAGS= -ansi -pedantic -Wall -g -c
LDFLAGS= -g -o

$(MODULE_TARGET): $(MODULE_OBJ)
	gcc $(MODULE_OBJ) -lpgn $(LDFLAGS) ./$(MODULE_TARGET)

.cpp.o:
	gcc $(CCFLAGS) $< $(MODULE_INCS)

clean:
	- rm -f *.o
	- rm -f ./$(MODULE_TARGET)

