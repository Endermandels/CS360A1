# Assignment 1
# 9/5/2023
# CS 360
# Elijah Delavar
#
# Files:
#	main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile

EXEC = pairsofwords
OBJS = main.o wordPairCounting.o hash.o getWord.o crc64.o
FLAGS = gcc

$(EXEC): $(OBJS)
	$(FLAGS) -o $(EXEC) $(OBJS)

main.o: main.c
	$(FLAGS) -c main.c

wordPairCounting.o: wordPairCounting.c wordPairCounting.h
	$(FLAGS) -c wordPairCounting.c

hash.o: hash.c hash.h
	$(FLAGS) -c hash.c

getWord.o: getWord.c getWord.h
	$(FLAGS) -c getWord.c

crc64.o: crc64.c crc64.h
	$(FLAGS) -c crc64.c

clean:
	rm *.o
	rm $(EXEC)

run: $(EXEC)
	./$(EXEC) mobydick.txt
