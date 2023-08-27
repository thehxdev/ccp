SRC_DIR := ./src
OBJS_DIR := ./objs
OUT_DIR := ./release
OUT_HEADERS_DIR := ./release/ccp

OBJS := ccp.o ccp_flag.o ccp_list.o str.o
LIBCCP_A  := libccp.a

CC := gcc
CFLAGS := -std=c17 -Wall -Wextra -ggdb
CFLAGS += -Werror -Wno-unused-result


$(LIBCCP_A): dir $(OBJS)
	ar -rsc $(OUT_DIR)/$(LIBCCP_A) $(foreach file,$(OBJS),$(OBJS_DIR)/$(file))
	cp $(SRC_DIR)/*.h $(OUT_HEADERS_DIR)


%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $(OBJS_DIR)/$*.o $(SRC_DIR)/$*.c


example: example.c $(LIBCCP_A)
	$(CC) $(CFLAGS) -I$(OUT_HEADERS_DIR) -o example.o -c $<
	$(CC) -o example ./example.o -L$(OUT_DIR) -lccp

dir:
	@mkdir -p $(OUT_DIR) $(OUT_HEADERS_DIR)

clean:
	rm -rf ./release $(OBJS_DIR) a.out example *.o
