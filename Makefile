CC = gcc
BDIR = build

all: conf core-per

conf: conf.c graph.c
	$(CC) -o $(BDIR)/conf.exe conf.c graph.c -I.

core-per: core-per.c graph.c
	$(CC) -o $(BDIR)/core-per.exe core-per.c graph.c -I.


.PHONY: all clean

clean:
	rm -f $(BDIR)/*.exe