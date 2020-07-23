TARGET = main

SRC = src
INCLUDE = include
BIN = bin

SOURCE = $(wildcard $(SRC)/*.cpp)
OBJECT = $(patsubst %,$(BIN)/%, $(notdir $(SOURCE:.cpp=.o)))

CC = g++
CFLAGS = -Wall -I $(INCLUDE)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(TARGET)

$(BIN)/%.o: $(SRC)/%.cpp $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir $(BIN)

run: $(TARGET)
	$(TARGET)

clean:
	rm -f -r $(TARGET) $(BIN)