EXEC_NAME = main.exe
TEST_EXEC = test.exe
INC = ../inc
BIN = ../bin
OUT = ../out
SRC = ../src
TEST = ../tst
EXE_OBJ = $(OUT)/main.o

# Compile cpp to object file
GC = g++ -c -g

# Link object files to exe
GO = g++ -g -o

STD = -std=c++11

all: clean make_dir $(EXEC_NAME)

test: clean make_dir
	g++ $(STD) $(TEST)/main.cpp $(SRC)/kvnode.cpp $(SRC)/queryparser.cpp \
	$(SRC)/memtable.cpp $(SRC)/queryexecutor.cpp \
	$(SRC)/utils.cpp -lgtest -o $(OUT)/$(TEST_EXEC)

make_dir:
	mkdir $(BIN)
	mkdir $(OUT)

clean:
	rm -rf $(BIN)
	rm -rf $(OUT)

$(EXEC_NAME): main.o objects
	$(GO) $(BIN)/$(EXEC_NAME) $(OUT)/*.o

main.o:
	$(GC) $(SRC)/main.cpp -o $(OUT)/main.o

objects:
	$(GC) $(SRC)/kvnode.cpp -o $(OUT)/kvnode.o
	$(GC) $(SRC)/memtable.cpp -o $(OUT)/memtable.o
	$(GC) $(SRC)/queryparser.cpp -o $(OUT)/queryparser.o
	$(GC) $(SRC)/queryexecutor.cpp -o $(OUT)/queryexecutor.o
	$(GC) $(SRC)/utils.cpp -o $(OUT)/utils.o


