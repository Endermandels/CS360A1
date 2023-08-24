EXEC = pairsofwords
OBJS = main.o wordPairCounting.o hash.o getWord.o
FLAGS = gcc

$(EXEC): $(OBJS)
	$(FLAGS) -o $(EXEC) $(OBJS)

main.o: main.c
	$(FLAGS) -c main.c

wordPairCounting.o: wordPairCounting.c
	$(FLAGS) -c wordPairCounting.c

hash.o: hash.c
	$(FLAGS) -c hash.c

getWord.o: getWord.c
	$(FLAGS) -c getWord.c

run: $(EXEC)
	./$(EXEC)

runv: $(EXEC)
	valgrind ./$(EXEC)

runv0: $(EXEC)
	valgrind ./$(EXEC) test.txt

runv1: $(EXEC)
	valgrind ./$(EXEC) gettysburg.txt

runv2: $(EXEC)
	valgrind ./$(EXEC) gettysburg.txt dracula.txt
