#OBJECTS = cmpfile.o dupcheck.o skiplist.o tdir.o main.o
#HEAD_FILE = cmpfile.h dupcheck.h skiplist.h tdir.h main.h
CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall
TARGET = DupfilesChecker

.PHONY : rebuild clean
all : $(TARGET)

DupfilesChecker : $(OBJ) 
	$(CC) -o $@ $(CFLAGS) $^ 

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SRC:.c=.d)

rebuild : clean all

clean : 
	find . -name "*.o"  | xargs rm -f
	find . -name "*.exe" | xargs rm -f
	find . -name "*.d"  | xargs rm -f
	rm -f $(TARGET)