CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc


# recompile if this heder changes
HEADERS = odbc.h products.h orders.h customers.h 
DEPS = odbc.o products.o  orders.o customers.o

EXE = menu
OBJ = $(EXE).o
all: $(EXE)

%.o: %.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(DEPS) $(OBJ)
	$(CC) -o $(EXE) $(DEPS) $(OBJ) $(LDLIBS)

clean :
	rm -f *.o core $(EXE)


