all : qua

qua : qua.c
	gcc -o qua qua.c 

clean :
	rm qua
