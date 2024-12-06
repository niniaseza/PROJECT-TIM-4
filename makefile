CC = gcc
CFLAGS = -Wall -g
OBJS = projekpemro.o library.o

all : projekpemro

projekpemro : $(OBJS)
	$(CC) -o projekpemro $(OBJS)

projekpemro.o : projekpemro.c library.h 
	$(CC) $(CFLAGS) -c projekpemro.c
	
library.o : library.c library.h
	$(CC) $(CFLAGS) -c library.c

clean:
	rm -f *.o projekpemro.clean

