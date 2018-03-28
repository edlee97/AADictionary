#--------------------------------------------------------------------------
# Makefile
# Edward Lee
# Makefile. ATTENTION: NOT MADE BY ME!
# #--------------------------------------------------------------------------

FLAGS   = -std=c99 -Wall
SOURCES = Dictionary.c DictionaryClient.c
OBJECTS = Dictionary.o DictionaryClient.o
HEADERS = Dictionary.h
EXEBIN  = DictionaryClient

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS) DictionaryTest.o DictionaryTest

DictionaryTest :
	gcc -c $(FLAGS) Dictionary.c DictionaryTest.c
	gcc -o DictionaryTest Dictionary.o DictionaryTest.o

check:
	valgrind --leak-check=full $(EXEBIN) 

submit:
	submit cmps012b-pt.s16 pa5 README Dictionary.c DictionaryTest.c DictionaryClient.c Makefile Dictionary.h
