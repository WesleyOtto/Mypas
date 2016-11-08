CFLAGS=-I. -g

project = mypas 

relocatables= mypas.o lexer.o parser.o keywords.o symtab.o

executable= $(project)

$(executable): $(relocatables)
	cc -o $(executable) $(relocatables)
clean:
	$(RM)  $(relocatables)
mostlyclean: clean
	$(RM) $(executable) *~
indent:
	indent -nfca -orig -nuts -ts4 *.[ch]
