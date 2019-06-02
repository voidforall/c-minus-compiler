parser: lex.yy.cpp parser.tab.cpp parser.tab.h util.cpp main.cpp lexer.h util.h globals.cpp gencode.cpp analyze.h symtab.h gencode.h code.cpp code.h analyze.cpp gentiny.cpp gentiny.h
	g++ -o parser main.cpp util.cpp lex.yy.cpp parser.tab.cpp globals.cpp analyze.cpp gencode.cpp symtab.cpp code.cpp gentiny.cpp -std=c++11  -w

lex.yy.cpp: lexer.l parser.tab.h globals.h symtab.h
	lex -o lex.yy.cpp lexer.l 

parser.tab.h parser.tab.cpp: parser.y globals.h symtab.h
	bison -d parser.y -o parser.tab.cpp

clean: 
	rm -f lex.yy.c y.tab.c y.tab.h parser parser.tab.h parser.tab.c


