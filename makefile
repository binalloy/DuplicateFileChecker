OBJECTS = cmpfile.o dupcheck.o skiplist.o tdir.o main.o
HEAD_FILE = cmpfile.h dupcheck.h skiplist.h tdir.h main.h

lab3 : $(OBJECTS)  $(HEAD_FILE)
	gcc -o lab3 $(OBJECTS) 

cmpfile.o : cmpfile.c
	gcc -c -Wall cmpfile.c
dupcheck.o : dupcheck.c
	gcc -c -Wall dupcheck.c
skiplist.o : skiplist.c
	gcc -c -Wall skiplist.c
tdir.o: tdir.c
	gcc -c -Wall tdir.c
main.o: main.c
	gcc -c -Wall main.c

.PHONY : clean
clean : 
	find . -name "*.o"  | xargs rm -f
	find . -name "*.exe" | xargs rm -f

rebuild :
	make clean
	make