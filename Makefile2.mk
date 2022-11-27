# Makefile para Windows

PROG = octree.exe
FONTES = octree.c
OBJETOS = $(FONTES:.c=.o)
CFLAGS = -O3 -g -Iinclude # -Wall -g  # Todas as warnings, infos de debug

# Troque -Llib\GL por -Llib\GL\x64 se estiver utilizando o MinGW 64!
LDFLAGS = -Llib\GL -lfreeglut -lopengl32 -lglu32 -lm

CC = gcc

$(PROG): $(OBJETOS)
	gcc $(CFLAGS) $(OBJETOS) -o $@ $(LDFLAGS)

clean:
	-@ del $(OBJETOS) $(PROG)