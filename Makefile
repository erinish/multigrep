queue.o: queue.c
	gcc -g -c queue.c
queue: queue.o
	gcc -g queue.o -o queue
multigrep.o: multigrep.c
	gcc -c multigrep.c
multigrep: multigrep.o queue.o
	gcc -g queue.o multigrep.o -o multigrep
