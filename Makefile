parser: lex.yy.c parser.tab.c parser.tab.h util.cpp main.cpp lexer.h util.h globals.cpp
	g++ -o parser main.cpp util.cpp lex.yy.c parser.tab.c globals.cpp -std=c++11  -w

lex.yy.c: lexer.l parser.tab.h globals.h
	lex lexer.l

parser.tab.h parser.tab.c: parser.y globals.h
	bison -d parser.y

clean: 
	rm -f lex.yy.c y.tab.c y.tab.h parser parser.tab.h parser.tab.c


