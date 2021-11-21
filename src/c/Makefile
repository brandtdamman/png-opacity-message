CC = gcc
FFLAGS = -Wall -g
LFLAGS = -lm -g
OBJECTS = main.o encoding.o

.PHONY: clean

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f *.exe *.o
