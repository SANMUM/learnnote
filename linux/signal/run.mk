CC = gcc

CFLAGS = -O1 -Wall -I .
LDLIBS = -lpthread -lm

COUNTERARGS = -O1 -Wall 

# NOTE: we expect sharing.c to generate warnings
PROGS =	s_suspend\
		s_spend

all: $(PROGS)

# The two programs that we use to illustrate synchronization
# goodcnt: goodcnt.c csapp.c csapp.h
# 	$(CC) $(COUNTERARGS) -o goodcnt goodcnt.c csapp.c -lpthread
# 	$(CC) $(COUNTERARGS) -S goodcnt.c

s_suspend: s_suspend.c
	$(CC) $(COUNTERARGS) -o s_suspend s_suspend.c
s_spend: s_spend.c
# server: server.c

# client: client.c

# my_server: my_server.c
# my_client: my_client.c

clean:
	rm -f $(PROGS) *.o *~
