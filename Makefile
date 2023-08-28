EXEC = pairsofwords
OBJS = main.o wordPairCounting.o hash.o getWord.o crc64.o
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

crc64.o: crc64.c
	$(FLAGS) -c crc64.c

run: $(EXEC)
	./$(EXEC)

runv: $(EXEC)
	valgrind ./$(EXEC)

runv0: $(EXEC)
	valgrind ./$(EXEC) test.txt

runv01: $(EXEC)
	valgrind ./$(EXEC) -3 test.txt

runv1: $(EXEC)
	valgrind ./$(EXEC) gettysburg.txt

runv2: $(EXEC)
	valgrind ./$(EXEC) gettysburg.txt dracula.txt

runv3: $(EXEC)
	valgrind ./$(EXEC) -5 mobydick.txt
