queue.o: queue.c
	gcc -c queue.c
queue: queue.o
	gcc queue.o -o queue
multigrep.o: multigrep.c
	gcc -c multigrep.c
multigrep: multigrep.o queue.o
	gcc queue.o multigrep.o -o multigrep
