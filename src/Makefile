CC=g++
CFLAGS=-g -Wall
BIN=base64.o
RUN=run

all: $(RUN)

cli:
	$(CC) $(CFLAGS) -DCOMPILE_CLI base64.cpp -o bs64

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

$(RUN): $(RUN).cpp $(BIN)
	$(CC) $(CFLAGS) $^ -o $@.exe

clean:
	rm -f *.exe *.out *.o
