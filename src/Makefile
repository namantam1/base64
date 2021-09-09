CC=g++
CFLAGS=-g -Wall
BIN=base64.o
RUN=run

all: $(RUN)

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

$(RUN): $(RUN).cpp $(BIN)
	$(CC) $(CFLAGS) $^ -o $@.exe

clean:
	rm -f *.exe *.out *.o
