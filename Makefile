# Project
PROJECT := cstr
CC := gcc
CFLAGS = -Wall -Wextra -Werror -Wunused-result -Wconversion
LDFLAGS = -L/usr/local/lib -lcvec -lcarena
CPPFLAGS = -Iinclude

# Dirs
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include
TEST_DIR := test
EXAMPLE_DIR := example
OBJ_DIR := $(BUILD_DIR)/obj
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include
DOC_DIR := doc

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_MAIN := $(TEST_DIR)/test.c
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c
TEST_EXE := $(BUILD_DIR)/test
EXAMPLE_EXE := $(BUILD_DIR)/example
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so

# Rules
.PHONY: all debug test example tags clean install uninstall doc

all: CPPFLAGS += -DNDEBUG
all: CFLAGS += -O3 -march=native -flto
all: $(LIB_A) $(LIB_SO)
	
debug: $(LIB_A) $(LIB_SO)

test: LDFLAGS += -lctest
test: CPPFLAGS += -DTEST
test: $(TEST_EXE)

example: LDFLAGS += -lcstr
example: $(EXAMPLE_EXE)

tags:
	ctags -R --c-kinds=+p+d /usr/local/include /usr/include .

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) compile_commands.json tags

install:
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

uninstall:
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_A)))
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_SO)))
	rm $(addprefix $(INC_INSTALL_DIR)/, $(notdir $(INC)))

doc:
	doxygen

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TEST_EXE): $(TEST_MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(EXAMPLE_EXE): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
