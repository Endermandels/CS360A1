EXEC = pairsofwords
OBJS = main.o wordPairCounting.o hash.o
FLAGS = gcc

$(EXEC): $(OBJS)
	$(FLAGS) -o $(EXEC) $(OBJS)

main.o: main.c
	$(FLAGS) -c main.c

wordPairCounting.o: wordPairCounting.c
	$(FLAGS) -c wordPairCounting.c

hash.o: hash.c
	$(FLAGS) -c hash.c

run: $(EXEC)
	./$(EXEC)

runv: $(EXEC)
	valgrind ./$(EXEC)

runv1: $(EXEC)
	valgrind ./$(EXEC) gettysburg.txt