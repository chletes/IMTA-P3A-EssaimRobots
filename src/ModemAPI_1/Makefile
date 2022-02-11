CC=gcc # compilateur
CFLAGS=-pthread # options de compilation

# The CFLAGS variable sets compile flags for gcc:
#  -g          compile with debug information
#  -Wall       give verbose compiler warnings
#  -pthread    add support for multithreading

all: clean modemAPI_v1

modemAPI_v1: modem/modem.o main/main.o
	$(CC) $(CFLAGS) $^ -o modemAPI_v1.out
	@echo ""

modem.o: modem/modem.c
	@echo "* Building project..."
	$(CC) -g $(CFLAGS) -c $^ -o modem/modem.o

main.o: main/main.c
	$(CC) -g $(CFLAGS) -c $^ -o main/main.o

clean:
	@echo "* Cleaning project..."
	rm -rf */*.o modemAPI_v1.out
	@echo ""
	@echo "* Building project..."

