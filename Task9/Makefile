CPPFLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
HEADERS = command.h command_type.h list_node.h lists.h record.h config.h bree.h btree_node.h hash.h hashphone.h ordering.h list1.h list3.h
MATH = -lm

%.o: %.cpp $(HEADERS)
	g++ -c $(CPPFLAGS) $<
%.out: %.o
	g++ $(CPPFLAGS) $^ -o $@ 
all: a.out

archive:
	zip Vatchenko_MY.zip Makefile *.cpp *.h config.txt

rmarchive:
	rm Vatchenko_MY.zip

clean:
	rm -f *.o *.out all
