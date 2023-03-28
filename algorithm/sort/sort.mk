
PROGS =	countSort radixSort buckSort bucketsort shellsort heapsort mergesort quicksort selectsort bubblesort insertsort 

all:	$(PROGS) $(MEMSTR)

%:	%.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)

