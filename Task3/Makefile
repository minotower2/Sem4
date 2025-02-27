CPPFLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
FUNCTIONS_O = solve.o
HEADERS = btree.h btree_node.h querry.h solve.h rb_tree.h
MATH = -lm

%.o: %.cpp $(HEADERS)
	g++ -c $(CPPFLAGS) $<
%.out: %.o $(FUNCTIONS_O)
	g++ $(CPPFLAGS) $^ -o $@ 
all: a01.out a02.out a04.out a05.out

archive:
	zip Vatchenko_MY.zip Makefile *.cpp *.h 

rmarchive:
	rm Vatchenko_MY.zip

clean:
	rm -f *.o *.out all
