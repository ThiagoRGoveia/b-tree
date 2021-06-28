all:
	gcc -o exec *.c

run:
	./exec

zip:
	@zip -r trabalho.zip *.c *.h Makefile nodes.dat data.dat
