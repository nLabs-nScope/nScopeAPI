all: nscopetest

CC=gcc
CFLAGS+=-I../ -Wall -g -c
LIBS=libnscope.so
COBJS=
CPP_FILES = $(wildcard ../*.cpp)
CPPOBJS= $(CPP_FILES:.cpp=.o)
OBJS=$(COBJS) $(CPPOBJS)

nscopetest: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o nscopetest

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) nscopetest

.PHONY: clean

.INTERMEDIATE:  $(OBJS)
