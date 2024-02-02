CC = g++
CFLAGS = -std=c++2a -g
LDFLAGS = -lncurses

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
EXEC = age

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
