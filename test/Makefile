CC = gcc
CFLAGS = -Wall -Werror -pedantic -g

DIR_BLD = bld
DIR_OBJ = $(DIR_BLD)/obj

SRC = ./test.c ../string.c
DIR_SRC = $(sort $(dir $(SRC)))
OBJ = $(addprefix $(DIR_OBJ)/,$(notdir $(SRC:.c=.o)))

vpath %.c $(DIR_SRC)

TARGET = $(DIR_BLD)/test


$(TARGET) : $(OBJ) | $(DIR_BLD)
	$(CC) $(CFLAGS) $(OBJ) -o $@


$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


$(DIR_OBJ) $(DIR_BLD):
	mkdir -p $@


.PHONY: clean
clean: ; rm -rf $(DIR_BLD)
