all: schedule.o

schedule.o: schedule.c
	gcc -o schedule.o schedule.c

clean:
	rm -f schedule.o

