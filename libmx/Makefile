CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC = src
OBJ = obj
LIBRARY = libmx.a

SRCS = $(wildcard $(SRC)/*.c)

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all:
	make LIBMX

LIBMX: $(LIBRARY)

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	rm -rf $(OBJ)

uninstall:
	rm -f $(LIBRARY)

reinstall: uninstall all
