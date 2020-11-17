CC = gcc -g
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc

export PGDATABASE:=classicmodels
export PGUSER:=alumnodb
export PGPASSWORD:=alumnodb
export PGCLIENTENCODING:=LATIN9
export PGHOST:=localhost

DBNAME =$(PGDATABASE)
NEWDBNAME = $(PGNEWDATABASE)
PSQL = psql
CRATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore


# recompile if this heder changes
HEADERS = odbc.h products.h orders.h customers.h 
DEPS = odbc.o products.o  orders.o customers.o

EXE = menu
OBJ = $(EXE).o
compile : $(EXE)
all: dropdb createdb restore shell

createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)

psql: shell
shell:
	@echo create psql shell
	@$(PSQL)



%.o: %.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(DEPS) $(OBJ)
	$(CC) -o $(EXE) $(DEPS) $(OBJ) $(LDLIBS)

clean :
	rm -f *.o core $(EXE)


