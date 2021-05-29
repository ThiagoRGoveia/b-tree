all:
	gcc -o exec *.c

run:
	./exec

zip:
	@zip -r exercicio.zip *.c *.h Makefile
