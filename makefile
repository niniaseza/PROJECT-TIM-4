CC = gcc
CFLAGS = -Wall -g
OBJS = projekpemro.o library.o

all : projekpemro

projekpemro : $(OBJS)
	$(CC) -o projekpemro $(OBJS)

