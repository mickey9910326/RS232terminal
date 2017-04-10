CC = gcc
CFLAGS = -Wall -gdwarf-2 -std=gnu99 -o2
LIBSRC = rs232.c
LIBOBJ = ${LIBSRC:.c=.o}

terminal :
	@gcc terminal.c rs232.c -Wall -Wextra -lpthread -o2 -o terminal
