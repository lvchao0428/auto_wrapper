main:main.o read_html.o ext_spc_html.o mystring.o savehtml.o test.o log.o code_convert.o 
	gcc -g -o main main.o read_html.o ext_spc_html.o mystring.o savehtml.o test.o log.o code_convert.o -lgumbo -lcurl 
main.o:main.c
	gcc -g -c main.c
read_html.o:read_html.c 
	gcc -g -c read_html.c -lgumbo
ext_spc_html.o:ext_spc_html.c 
	gcc -g -c ext_spc_html.c -lgumbo
mystring.o:mystring.c
	gcc -g -c mystring.c
savehtml.o:savehtml.c
	gcc -g -c savehtml.c
code_convert.o:code_convert.c
	gcc -g -c code_convert.c
test.o:test.c
	gcc -g -c test.c
log.o:log.c
	gcc -g -c log.c
clean:
	rm *.o main
