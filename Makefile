CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC = ./src
OBJ = ./obj
LIB = ./libmx

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
LIBRARY = ./libmx/libmx.a
BINARY = pathfinder

all:
	make PATHFINDER

PATHFINDER: $(BINARY)

$(BINARY): $(LIBRARY) $(OBJS)
	${CC} ${CFLAGS} ${OBJS} -o ${BINARY} $(LIBRARY)

$(LIBRARY):
	cd $(LIB) && make

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	cd $(LIB) && make clean
	rm -rf $(OBJ)

uninstall:
	cd $(LIB) && make uninstall
	rm -f $(BINARY)

reinstall: uninstall all
