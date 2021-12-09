CC = gcc
FFLAGS = -Wall -fopenmp
LFLAGS = -lm -lpng -lgomp
OBJECTS = main.o image.o encoding.o

.PHONY: clean

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f *.exe *.o
