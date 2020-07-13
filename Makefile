all: copy

copy: 
	gcc -o copy copy.c

clean: 
	rm -f copy
