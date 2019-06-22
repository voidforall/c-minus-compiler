CC = g++
SRC_DIR = src
BUILD_DIR = build
LEX = flex
YACC = bison
CFLAGS = -std=c++11 -Wno-deprecated-register -Wno-writable-strings

# objects
_OBJS = lex.yy.o parser.tab.o util.o main.o globals.o gencode.o analyze.o code.o gentiny.o symtab.o
OBJS = $(patsubst %,$(BUILD_DIR)/%,$(_OBJS))

# .h
_DEPS = parser.tab.h util.h globals.h gencode.h analyze.h code.h gentiny.h symtab.h parser.h lexer.h
DEPS = $(patsubst %,$(SRC_DIR)/%,$(_DEPS))


cminus: $(OBJS)
	$(CC) -o cminus $(OBJS) $(CFLAGS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(SRC_DIR)/lex.yy.cpp: $(SRC_DIR)/lexer.l $(DEPS)
	$(LEX) -o $@ $< 

$(SRC_DIR)/parser.tab.h $(SRC_DIR)/parser.tab.cpp: $(SRC_DIR)/parser.y $(DEPS)
	$(YACC) --defines=$(SRC_DIR)/parser.tab.h $< -o $(SRC_DIR)/parser.tab.cpp

tm:
	gcc -o tm tm.c

.PHONY: clean
clean:
	-rm -rf $(OBJS)
	-rm -rf $(SRC_DIR)/lex.yy.cpp $(SRC_DIR)/parser.tab.h $(SRC_DIR)/parser.tab.cpp
	-rm cminus
