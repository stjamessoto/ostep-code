FLAGS = -Wall -pthread -g

all: main-race-locked-one main-race-locked-both main-race-removed-line

clean:
	rm -f main-race-locked-one main-race-locked-both main-race-removed-line

main-race-locked-one: main-race-locked-one.c mythreads.h
	gcc -o main-race-locked-one main-race-locked-one.c $(FLAGS)

main-race-locked-both: main-race-locked-both.c mythreads.h
	gcc -o main-race-locked-both main-race-locked-both.c $(FLAGS)

main-race-removed-line: main-race-removed-line.c mythreads.h
	gcc -o main-race-removed-line main-race-removed-line.c $(FLAGS)
