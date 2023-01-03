better_ping.o: better_ping.c
	gcc -Wall -c better_ping.c

watchdog.o: watchdog.c
	gcc -Wall -c watchdog.c

ping.o: ping.c
	gcc -Wall -c ping.c

parta: ping.o
	gcc -Wall -o parta ping.o

partb: better_ping.o watchdog.o
	gcc -Wall -o partb better_ping.o

all: parta partb

.PHONY: clean all

clean:
	rm -f *.o *.out parta partb watchdog *.gch