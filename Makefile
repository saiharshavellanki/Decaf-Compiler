bcc:	parser.tab.c lex.yy.c classes.h classes.cpp
	g++ -w -g -std=c++11 parser.tab.c  classes.cpp -lfl -ltinfo -lpthread -ldl -o ast
parser.tab.c: parser.y
	bison -d -v parser.y
parser.tab.h: parser.y
	bison -d  parser.y
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean
clean:
	-@rm -rf parser.tab.c parser.output parser.tab.h lex.yy.c bcc 2>/dev/null || true
