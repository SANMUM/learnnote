CC = gcc

CFLAGS = -O1 -Wall -I .
LDLIBS = -lpthread -lm

COUNTERARGS = -O1 -Wall 

# NOTE: we expect sharing.c to generate warnings
PROGS =	epoll_ser\
		poll_cli\
		poll_ser\
		select_client\
		select\
		client\
		server\
		my_server\
		my_client


all: $(PROGS)

# The two programs that we use to illustrate synchronization
# goodcnt: goodcnt.c csapp.c csapp.h
# 	$(CC) $(COUNTERARGS) -o goodcnt goodcnt.c csapp.c -lpthread
# 	$(CC) $(COUNTERARGS) -S goodcnt.c

select: select.c 
	$(CC) $(COUNTERARGS) -o select select.c -lpthread
	# $(CC) $(COUNTERARGS) -S badcnt.c
select_client: select_client.c
	$(CC) $(COUNTERARGS) -o select_client select_client.c -lpthread
poll_ser: poll_ser.c 
poll_cli: poll_cli.c
epoll_ser: epoll_ser.c

server: server.c

client: client.c

my_server: my_server.c
my_client: my_client.c

clean:
	rm -f $(PROGS) *.o *~
