SRC_DIR := ./src
OBJS_DIR := ./objs
OUT_LIB_DIR := ./release/lib
OUT_HEADERS_DIR := ./release/ccp


OBJS := ccp.o ccp_flag.o ccp_list.o str.o
LIBCCP := libccp.a

CC := gcc
FLAGS := -std=c17 -Wall -Wextra
FLAGS += -Werror -Wno-unused-result -Wno-unused-variable


$(LIBCCP): $(OBJS)
	@mkdir -p $(OUT_LIB_DIR) $(OUT_HEADERS_DIR)
	ar -rsc $(OUT_LIB_DIR)/$(LIBCCP) $(foreach file,$(OBJS),$(OBJS_DIR)/$(file))
	cp $(SRC_DIR)/*.h $(OUT_HEADERS_DIR)


%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) -c -o $(OBJS_DIR)/$*.o $(SRC_DIR)/$*.c


example: example.c $(LIBCCP)
	$(CC) $(FLAGS) -I$(OUT_HEADERS_DIR) -o example.o -c $<
	$(CC) -o example ./example.o $(OUT_LIB_DIR)/$(LIBCCP) 

clean:
	rm -rf ./release $(OBJS_DIR) a.out example *.o
