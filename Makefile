CC = gcc
MKDIR_P = mkdir -p
BDIR = build

all: conf core-per

conf: conf.c graph.c
	$(MKDIR_P) $(BDIR)
	$(CC) -o $(BDIR)/conf.exe conf.c graph.c -I.

core-per: core-per.c graph.c
	$(MKDIR_P) $(BDIR)
	$(CC) -o $(BDIR)/core-per.exe core-per.c graph.c -I.

test: test.c graph.c
	$(MKDIR_P) $(BDIR)
	$(CC) -o $(BDIR)/test.exe test.c graph.c -I.


.PHONY: all clean

clean:
	rm -r $(BDIR)
