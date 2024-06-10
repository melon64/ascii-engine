CC = g++
CFLAGS = -std=c++2a -g -I./engine
LDFLAGS = -lncurses

ENGINE_DIR = ./engine
MAIN_DIR = .
SRCS = $(wildcard $(MAIN_DIR)/*.cc) $(wildcard $(ENGINE_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)
EXEC = age

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(ENGINE_DIR)/%.o: $(ENGINE_DIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
