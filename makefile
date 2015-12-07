main:main.o read_html.o ext_spc_html.o mystring.o 
	gcc -g -o main main.o read_html.o ext_spc_html.o mystring.o -lgumbo
main.o:main.c
	gcc -g -c main.c
read_html.o:read_html.c 
	gcc -g -c read_html.c -lgumbo
ext_spc_html.o:ext_spc_html.c 
	gcc -g -c ext_spc_html.c -lgumbo
mystring.o:mystring.c
	gcc -g -c mystring.c
clean:
	rm *.o main
