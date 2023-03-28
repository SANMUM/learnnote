CC = gcc

CFLAGS = -O1 -Wall -I .
LDLIBS = -lpthread -lm

COUNTERARGS = -O1 -Wall 

# NOTE: we expect sharing.c to generate warnings
PROGS =	badcnt\
		test_join\
		test_exit\
		test_cancel\
		goodcnt\
		test_mutex\
		test_sem\
		test_cond\
		test_detach

all: $(PROGS)

# The two programs that we use to illustrate synchronization
# goodcnt: goodcnt.c csapp.c csapp.h
# 	$(CC) $(COUNTERARGS) -o goodcnt goodcnt.c csapp.c -lpthread
# 	$(CC) $(COUNTERARGS) -S goodcnt.c

badcnt: badcnt.c 
	$(CC) $(COUNTERARGS) -o badcnt badcnt.c -lpthread
	# $(CC) $(COUNTERARGS) -S badcnt.c
test_join: test_join.c
	$(CC) $(COUNTERARGS) -o test_join test_join.c -lpthread 
test_exit: test_exit.c

test_cancel: test_cancel.c

goodcnt: goodcnt.c

test_mutex: test_mutex.c

test_sem: test_sem.c

test_cond: test_cond.c

test_detach: test_detach.c
clean:
	rm -f $(PROGS) *.o *~
