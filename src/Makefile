CC=gcc

sim:
	$(CC) -o sim main.c read_trace.c PT_Hashtable.c LRU.c Second_Chance.c frame.c statistics.c

.PHONY: clean

clean:
	rm  -f sim.o sim