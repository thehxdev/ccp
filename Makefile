SRC_DIR := ./src
OUT_DIR := ./release
OUT_HEADERS_DIR := ./release/ccp

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRC_FILES:.c=.o)
LIBCCP_A  := $(OUT_DIR)/libccp.a

CC := gcc
CFLAGS := -std=c17 -Wall -Wextra
CFLAGS += -Werror -Wno-unused-result
CFLAGS += -ggdb -Og
LIBS := -L$(OUT_DIR) -lccp


$(LIBCCP_A): $(OBJS)
	@mkdir -p $(OUT_DIR) $(OUT_HEADERS_DIR)
	ar -rsc $(LIBCCP_A) $(OBJS)
	cp $(SRC_DIR)/*.h $(OUT_HEADERS_DIR)


%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$*.c


example: example.c $(LIBCCP_A)
	$(CC) $(CFLAGS) -I$(OUT_HEADERS_DIR) -o example.o -c $<
	$(CC) -o example ./example.o $(LIBS)

clean:
	rm -rf $(OUT_DIR) example *.o $(SRC_DIR)/*.o
