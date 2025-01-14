COMPILER=gcc
MAIN=main.c
LIBS=ataraxia/classic/structures/matrix.h ataraxia/classic/structures/matrix.c
TESTS=tests/test_matrix.c

all: chill 

chill:
	$(COMPILER) -o main $(LIBS) $(MAIN) &&\
	$(COMPILER) -o run_tests $(LIBS) $(TESTS)

.PHONY:
	chill 
