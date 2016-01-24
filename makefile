COMPILER = cc
FLAGS = -std=c99 -Wall -Werror -pedantic -c
EXE = rmr
BINDIR = /usr/local/bin
MANDIR = /usr/local/share/man/man1

all: $(EXE)

rmr: rmr.o; \
    $(COMPILER) -o $(EXE) rmr.o

rmr.o: rmr.c; \
    $(COMPILER) $(FLAGS) rmr.c

clean:; \
    rm -rf *.o $(EXE)

install: all; \
	install -D $(EXE) $(BINDIR)/$(EXE)

uninstall:; \
	rm -f $(BINDIR)/$(EXE)

installman:; \
	install -D docs/$(EXE).1 $(MANDIR)/$(EXE).1

uninstallman:; \
	rm -f $(MANDIR)/$(EXE).1
