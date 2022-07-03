ALLSRC  := $(wildcard src/*.c) libs/ecsj/ecsj.c
SRC     := $(filter-out src/test.c, $(ALLSRC))
TESTSRC := $(filter-out src/main.c, $(ALLSRC))
PKGS    := 
CC      := gcc
CFLAGS  := -Iinclude -Ilibs
CFLAGS  += -Wall -O2 -std=gnu17 #$(shell pkg-config --cflags $(PKGS))
LDFLAGS := -lGL -lGLEW -lglfw -lsoil2 #/usr/local/lib/libsoil2.so #$(shell pkg-config --libs $(PKGS))
BINARY  := a.out

.PHONY: dev clean compile cnr

default: compile

dev:
	bear -- make compile
	rm $(BINARY)

clean:
	$(RM) *.o $(BINARY)

compile: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BINARY)

test-compile: $(TESTSRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BINARY)

cnr: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BINARY)
	./$(BINARY)
	$(RM) *.o $(BINARY)

tnr: $(TESTSRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BINARY)
	./$(BINARY)
	$(RM) *.o $(BINARY)
