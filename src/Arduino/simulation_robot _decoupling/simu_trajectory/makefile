EXEC = main
CC = g++

SRC = $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp 
	$(CC) -o $@ -c $<
	
.PHONY: clean 

clean:
	@rm -rf *.o $(EXEC)